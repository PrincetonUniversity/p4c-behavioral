/* Headers */

header_type ethernet_t {
    fields {
        dstAddr : 48;
        srcAddr : 48;
        etherType : 16;
    }
}

header_type vlan_t {
    fields {
        pcp : 3;
	    cfi : 1;
	    vid : 12;
	    etherType : 16;
    }
    //length  4;
    //max_length 4;
}

header_type intrinsic_metadata_t {
    fields {
        mcast_grp : 4;
        egress_rid : 4;
        mcast_hash : 16;
        lf_field_list: 32;
    }
}


header ethernet_t ethernet_;
header vlan_t vlan_;
metadata intrinsic_metadata_t intrinsic_metadata;

/* Parser */

#define VLAN_TYPE 0x8100

parser start {
    return parse_ethernet;
}

parser parse_ethernet {
    extract(ethernet_);
    return select (ethernet_.etherType) {
        VLAN_TYPE : parse_vlan;
        default : ingress;
    }
}

parser parse_vlan {
    extract(vlan_);
    return ingress;
}

/* Actions */

action _drop() {
    drop();
}

action _nop() {
}

action modify_vlan_vid(vid) {
    add_header(vlan_);
    modify_field(vlan_.etherType, ethernet_.etherType);
    modify_field(vlan_.vid, vid);
    modify_field(ethernet_.etherType, VLAN_TYPE);
}

#define MAC_LEARN_RECEIVER 1024

field_list mac_learn_digest {
    ethernet_.srcAddr;
    vlan_.vid;
    standard_metadata.ingress_port;
}

action generate_learn_notify() {
    generate_digest(MAC_LEARN_RECEIVER, mac_learn_digest);
}

action forward(port) {
    modify_field(standard_metadata.egress_spec, port);
}

action broadcast() {
    modify_field(intrinsic_metadata.mcast_grp, 1);
}

action strip_vlan() {
    modify_field(ethernet_.etherType, vlan_.etherType);
    remove_header(vlan_);
}

/* Match-Action Tables */

table admin_ctrl {
    reads {
        ethernet_.srcAddr : exact;
        ethernet_.dstAddr : exact;
    }
    actions {_drop; _nop;}
    size : 512;
}

table vlan_in_proc {
    reads {
        vlan_.pcp : exact;
        vlan_.cfi : exact;
        vlan_.vid : exact;
        standard_metadata.ingress_port : exact;
    }
    actions {modify_vlan_vid; _drop; _nop;}
    size : 512;
}

table mac_learn {
    reads {
        ethernet_.srcAddr : exact;
    }
    actions {generate_learn_notify; _nop;}
    size : 512;
}

table dst_lookup {
    reads {
        ethernet_.dstAddr : exact;
        vlan_.pcp : exact;
        vlan_.cfi : exact;
        vlan_.vid : exact;
    }
    actions {forward; broadcast;}
    size : 512;
}

table mcast_src_pruning {
    reads {
        standard_metadata.instance_type : exact;
    }
    actions {_nop; _drop;}
    size : 1;
}

// TODO: how to make sure that we only output the packets to the ports that carry our packet's VLAN, and that
// we include the 802.1Q header in the copy output to the trunk port but not in copies output to access ports

table output_proc {
    reads {
        standard_metadata.egress_port : exact;
    }
    actions {strip_vlan; _nop;}
    size : 16;
}

/* Control-Flow */

control ingress {
    apply(admin_ctrl);
    apply(vlan_in_proc);
    apply(mac_learn);
    apply(dst_lookup);
}

control egress {
    if(standard_metadata.ingress_port == standard_metadata.egress_port) {
        apply(mcast_src_pruning);
    }

    apply(output_proc);
}