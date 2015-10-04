/*
 * Copyright 2013-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * File:   ovs_action_ofp_actions.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_OFP_ACTIONS_H
#define	OVS_ACTION_OFP_ACTIONS_H 1

/* -- Called in lib/ofp-actions.h -- */
#define OVS_OFPACTS \
//::  for header_name in ordered_header_instances_regular:
    OFPACT(ADD_HEADER_${header_name.upper()}, ofpact_null, ofpact, "add_header_${header_name}") \
    OFPACT(RMV_HEADER_${header_name.upper()}, ofpact_null, ofpact, "rmv_header_${header_name}") \
//::  #endfor
    OFPACT(ADD_TO_FIELD, ofpact_add_to_field, ofpact, "add_to_field") \
    OFPACT(DEPARSE, ofpact_null, ofpact, "deparse") \
    \

/* -- Called in lib/ofp-actions.h -- */
#define OVS_OFPACT_STRUCTS \
    struct ofpact_add_to_field { \
        struct ofpact ofpact; \
        const struct mf_field *field; \
        bool flow_has_vlan; /* @Shahbaz: remove this. */ \
        union mf_value value; \
        union mf_value mask; \
    }; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_STRUCTS \
    struct ofp_action_add_to_field { \
        ovs_be16 type; /* @Shahbaz: remove this. */ \
        ovs_be16 len; /* Length is padded to 64 bits. */ \
        uint8_t pad[4]; \
    }; \
    OFP_ASSERT(sizeof(struct ofp_action_add_to_field) == 8); \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_FUNCTIONS \
//::  for header_name in ordered_header_instances_regular:
    static enum ofperr \
    decode_OFPAT_RAW_ADD_HEADER_${header_name.upper()}(struct ofpbuf *out) \
    { \
        ofpact_put_ADD_HEADER_${header_name.upper()}(out); \
        return 0; \
    } \
    \
    static void \
    encode_ADD_HEADER_${header_name.upper()}(const struct ofpact_null *null OVS_UNUSED, \
                             enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT_ADD_HEADER_${header_name.upper()}(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_ADD_HEADER_${header_name.upper()}(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                            enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put_ADD_HEADER_${header_name.upper()}(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format_ADD_HEADER_${header_name.upper()}(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "add_header_${header_name}"); \
    } \
    \
    static enum ofperr \
    decode_OFPAT_RAW_RMV_HEADER_${header_name.upper()}(struct ofpbuf *out) \
    { \
        ofpact_put_RMV_HEADER_${header_name.upper()}(out); \
        return 0; \
    } \
    \
    static void \
    encode_RMV_HEADER_${header_name.upper()}(const struct ofpact_null *null OVS_UNUSED, \
                         enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT_RMV_HEADER_${header_name.upper()}(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_RMV_HEADER_${header_name.upper()}(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                        enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put_RMV_HEADER_${header_name.upper()}(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format_RMV_HEADER_${header_name.upper()}(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "rmv_header_${header_name}"); \
    } \
    \
//::  #endfor
    static enum ofperr \
    decode_OFPAT_RAW_ADD_TO_FIELD(const struct ofp_action_add_to_field *oaatf, struct ofpbuf *ofpacts) \
    { \
        struct ofpact_add_to_field *atf; \
        enum ofperr error; \
        struct ofpbuf b; \
        \
        atf = ofpact_put_ADD_TO_FIELD(ofpacts); \
        \
        ofpbuf_use_const(&b, oaatf, ntohs(oaatf->len)); \
        ofpbuf_pull(&b, OBJECT_OFFSETOF(oaatf, pad)); \
        error = nx_pull_entry(&b, &atf->field, &atf->value, \
                              NULL); \
        if (error) { \
            return (error == OFPERR_OFPBMC_BAD_MASK \
                    ? OFPERR_OFPBAC_BAD_SET_MASK \
                    : error); \
        } \
        memset(&atf->mask, 0xff, atf->field->n_bytes); \
        \
        if (!is_all_zeros(b.data, b.size)) { \
            return OFPERR_OFPBAC_BAD_SET_ARGUMENT; \
        } \
        \
        /* OpenFlow says specifically that one may not set OXM_OF_IN_PORT via Set-Field. */ \
        if (atf->field->id == MFF_IN_PORT_OXM) { \
            return OFPERR_OFPBAC_BAD_SET_ARGUMENT; \
        } \
        \
        /* oxm_length is now validated to be compatible with mf_value. */ \
        if (!atf->field->writable) { \
            VLOG_WARN_RL(&rl, "destination field %s is not writable", \
                         atf->field->name); \
            return OFPERR_OFPBAC_BAD_SET_ARGUMENT; \
        } \
        \
        /* The value must be valid for match.  OpenFlow 1.5 also says, */ \
        /* "In an OXM_OF_VLAN_VID set-field action, the OFPVID_PRESENT bit must be */ \
        /* a 1-bit in oxm_value and in oxm_mask." */ \
        if (!mf_is_value_valid(atf->field, &atf->value) \
            || (atf->field->id == MFF_VLAN_VID \
                && (!(atf->mask.be16 & htons(OFPVID12_PRESENT)) \
                    || !(atf->value.be16 & htons(OFPVID12_PRESENT))))) { \
            struct ds ds = DS_EMPTY_INITIALIZER; \
            mf_format(atf->field, &atf->value, NULL, &ds); \
            VLOG_WARN_RL(&rl, "Invalid value for set field %s: %s", \
                         atf->field->name, ds_cstr(&ds)); \
            ds_destroy(&ds); \
            \
            return OFPERR_OFPBAC_BAD_SET_ARGUMENT; \
        } \
        return 0; \
    } \
    \
    static void \
    encode_ADD_TO_FIELD(const struct ofpact_add_to_field *atf, \
                   enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            struct ofp_action_add_to_field *oaatf OVS_UNUSED; \
            size_t start_ofs = out->size; \
            \
            oaatf = put_OFPAT_ADD_TO_FIELD(out); \
            out->size = out->size - sizeof oaatf->pad; \
            nx_put_entry(out, atf->field->id, ofp_version, &atf->value, &atf->mask); \
            pad_ofpat(out, start_ofs); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_ADD_TO_FIELD(char *arg, struct ofpbuf *ofpacts, \
                  enum ofputil_protocol *usable_protocols) \
    { \
        char *copy = xstrdup(arg); \
        struct ofpact_add_to_field *atf = ofpact_put_ADD_TO_FIELD(ofpacts); \
        char *value; \
        char *delim; \
        char *key; \
        const struct mf_field *mf; \
        char *error; \
        \
        value = arg; \
        delim = strstr(arg, "->"); \
        if (!delim) { \
            return xasprintf("%s: missing `->'", arg); \
        } \
        if (strlen(delim) <= strlen("->")) { \
            return xasprintf("%s: missing field name following `->'", arg); \
        } \
        \
        key = delim + strlen("->"); \
        mf = mf_from_name(key); \
        if (!mf) { \
            return xasprintf("%s is not a valid OXM field name", key); \
        } \
        if (!mf->writable) { \
            return xasprintf("%s is read-only", key); \
        } \
        atf->field = mf; \
        delim[0] = '\0'; \
        error = mf_parse(mf, value, &atf->value, &atf->mask); \
        if (error) { \
            return error; \
        } \
        \
        if (!mf_is_value_valid(mf, &atf->value)) { \
            return xasprintf("%s is not a valid value for field %s", value, key); \
        } \
        \
        *usable_protocols &= mf->usable_protocols_exact; \
        error = NULL; \
        \
        free(copy); \
        return error; \
    } \
    \
    static void \
    format_ADD_TO_FIELD(const struct ofpact_add_to_field *a, struct ds *s) \
    { \
        ds_put_cstr(s, "add_to_field:"); \
        mf_format(a->field, &a->value, &a->mask, s); \
        ds_put_format(s, "->%s", a->field->name); \
    } \
    \
    static enum ofperr \
    decode_OFPAT_RAW_DEPARSE(struct ofpbuf *out) \
    { \
        ofpact_put_DEPARSE(out); \
        return 0; \
    } \
    \
    static void \
    encode_DEPARSE(const struct ofpact_null *null OVS_UNUSED, \
                   enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT_DEPARSE(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_DEPARSE(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                  enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put_DEPARSE(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format_DEPARSE(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "deparse"); \
    } \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_SET_OR_MOVE_ACTION \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
    case OFPACT_DEPARSE: \
        return false; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_ALLOWED_IN_ACTIONS_SET \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
    case OFPACT_DEPARSE: \
        return false; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_INSTRUCTION_TYPE_FROM_OFPACT_TYPE \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
    case OFPACT_DEPARSE: \
        return OVSINST_OFPIT11_APPLY_ACTIONS; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_CHECK__ \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
    case OFPACT_DEPARSE: \
        return 0; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_OUTPUTS_TO_PORT \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
    case OFPACT_DEPARSE: \
        return false; \
    \

#endif	/* OVS_ACTION_OFP_ACTIONS_H */