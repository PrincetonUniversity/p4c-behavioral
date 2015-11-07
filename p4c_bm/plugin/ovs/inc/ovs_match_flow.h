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
 * File:   ovs_match_flow.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_FLOW_H
#define	OVS_MATCH_FLOW_H 1

//::  def byte_array_to_int(bytes):
//::    res = 0
//::    len_ = len(bytes)
//::    for i in xrange(len_):
//::      res += bytes[len_-1-i] << (8 * i)
//::    #endfor
//::    return res
//::  #enddef
//::
/* -- Called in lib/flow.h -- */
#define OVS_FIELDS \
//::  for header_name in ordered_header_instances_non_virtual:
//::    if header_name == "standard_metadata":
//::      continue
//::    #endif
    struct ${header_name}_padded_header ${header_name}; \
//::  #endfor
    \

/* -- Called in lib/flow.c -- */
#define OVS_MINIFLOW_EXTRACT_METADATA_DEFS \
//::  for header_name in ordered_header_instances_metadata:
//::    if header_name == "standard_metadata":
//::      continue
//::    #endif
    struct ${header_name}_padded_header ${header_name}; \
    bool is_${header_name}_touched = false;
//::  #endfor
    \

/* -- Called in lib/flow.c -- */
#define OVS_MINIFLOW_EXTRACT \
    OVS_MINIFLOW__START \
    \

//::  for state, parse_info in parse_states.items():
#define OVS_MINIFLOW__${state.upper()} \
//::    if OVS_PARSER_IMP == 0:
//::      # TODO: implement parser implementation style 0.
    OVS_MINIFLOW_OUT \
//::    elif OVS_PARSER_IMP == 1:
//::
//::      # Note: handle call sequence ###
//::      call_sequence = parse_info["call_sequence"]
//::      for call in call_sequence:
//::        type = call[0]
//::        if type == "extract":
//::          header_name = call[1]
    packet->${header_name}_ofs = (char *)data - l2; \
    struct ${header_name}_padded_header *${header_name}; \
    ${header_name} = (struct ${header_name}_padded_header *) data_pull(&data, &size, \
        sizeof(struct ${header_name}_header)); \
//::          # NOTE: this valid is used by the slow-path
    ${header_name}->${header_name}_valid = 1; \
//::          # TODO: offset increase should be based on header length expression, implement this.
    miniflow_push_words(mf, ${header_name}, ${header_name}, \
        sizeof(struct ${header_name}_padded_header) / sizeof(uint64_t)); \
    packet->${header_name} = *(struct ${header_name}_header *) ${header_name}; \
//::          # NOTE: this valid is used by the fast(data)-path
    packet->${header_name}_valid = 1; \
    \
//::        elif type == "set":
//::          destination = call[1]
//::          metadata_name = field_info[destination]["parent_header"]
//::          aligned_metadata_name = aligned_field_info[destination]["name"]
//::          aligned_metadata_mask = aligned_field_info[destination]["mask"]
//::          aligned_metadata_bit_offset_hdr = aligned_field_info[destination]["bit_offset_hdr"]
//::          aligned_metadata_bit_width = aligned_field_info[destination]["bit_width"]
//::
//::          source_type = call[2]
//::          if source_type == "immediate":
//::            source_value = hex(byte_array_to_int(call[3]))
//::            if aligned_metadata_mask:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = ((uint8_t)${source_value}) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = htons((uint16_t)${source_value}) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t)${source_value}) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t)${source_value}) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              else:
//::                assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            else:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = (uint8_t)${source_value}; \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = htons((uint16_t)${source_value}); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t)${source_value}); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t)${source_value}); \
//::              else:
//::                assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            #endif
//::          elif source_type == "latest":
//::            source = call[3]
//::            header_name = field_info[source]["parent_header"]
//::            aligned_field_name = aligned_field_info[source]["name"]
//::            aligned_field_mask = aligned_field_info[source]["mask"]
//::            aligned_field_bit_offset_hdr = aligned_field_info[source]["bit_offset_hdr"]
//::            aligned_field_bit_width = aligned_field_info[source]["bit_width"]
//::
//::            # NOTE: P4 specification assumes that the referenced source header in set_metadata() is already extracted
//::            # at this point.
//::            if header_name in ordered_header_instances_regular:
//::              if aligned_field_mask:
//::                if aligned_field_bit_width == 8:
    uint8_t value = (packet->${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \

//::                elif aligned_field_bit_width == 16:
    ovs_be16 value = (packet->${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 32:
    ovs_be32 value = (packet->${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 64:
    ovs_be64 value = (packet->${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                else:
//::                  assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              else:
//::                if aligned_field_bit_width == 8:
    uint8_t value = (packet->${header_name}.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 16:
    ovs_be16 value = (packet->${header_name}.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 32:
    ovs_be32 value = (packet->${header_name}.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 64:
    ovs_be64 value = (packet->${header_name}.${aligned_field_name}; \
//::                else:
//::                  assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              #endif
//::            elif header_name in ordered_header_instances_metadata:
//::              if aligned_field_mask:
//::                if aligned_field_bit_width == 8:
    uint8_t value = (${metadata_name}.hdr.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 16:
    ovs_be16 value = (${metadata_name}.hdr.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 32:
    ovs_be32 value = (${metadata_name}.hdr.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 64:
    ovs_be64 value = (${metadata_name}.hdr.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                else:
//::                  assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              else:
//::                if aligned_field_bit_width == 8:
    uint8_t value = (${metadata_name}.hdr.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 16:
    ovs_be16 value = (${metadata_name}.hdr.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 32:
    ovs_be32 value = (${metadata_name}.hdr.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 64:
    ovs_be64 value = (${metadata_name}.hdr.${aligned_field_name}; \
//::                else:
//::                  assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              #endif
//::            else:
//::              assert(False) # TODO: handle this case.
//::            #endif
//::
//::            if aligned_metadata_mask:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = ((uint8_t)value) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = ((ovs_be16)value) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = ((ovs_be32)value) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = ((ovs_be64)value) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              else:
//::                assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            else:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = (uint8_t)value; \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = (ovs_be16)value; \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = (ovs_be32)value; \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = (ovs_be64)value; \
//::              else:
//::                assert(False) # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            #endif
//::          else:
//::            assert(False) # TODO: handle this case (e.g., current() etc).
//::          #endif
    is_${metadata_name}_touched = true; \
    \
//::        else:
//::          assert(False) # TODO: handle this case.
//::        #endif
//::      #endfor
//::
//::      # Note: handle state transitions ###
//::      branch_on = parse_info['branch_on']
//::      branch_to = parse_info['branch_to']
//::      for case in branch_to:
//::        case_type, value, mask, next_state = case
//::        if not branch_on:
//::          assert(len(branch_to) == 1)
//::          if next_state[0] == "parse_state":
    OVS_MINIFLOW__${next_state[1].upper()} \
//::          elif next_state[0] == "table" or next_state[0] == "conditional_table":
    OVS_MINIFLOW_OUT \
//::          else:
//::            assert(False)
//::          #endif
//::        else:
//::          if case_type == "value":
    if ( \
//::            for key_type, key_value in branch_on:
//::              if key_type == "field_ref":
//::                header_name = field_info[key_value]["parent_header"]
//::                field_name = aligned_field_info[key_value]["name"]
//::                bit_width = aligned_field_info[key_value]["bit_width"]
//::                mask = aligned_field_info[key_value]["mask"]
//::                bit_offset_hdr = aligned_field_info[key_value]["bit_offset_hdr"]
//::                if bit_width == 8:
//::                  if mask:
        ((packet->${header_name}.${field_name} & ${hex(mask)}) >> ${bit_offset_hdr}) == ${hex(byte_array_to_int(value))} \
//::                  else:
        packet->${header_name}.${field_name} == ${hex(byte_array_to_int(value))} \
//::                  #endif
//::                elif bit_width == 16:
//::                  if mask:
        ((ntohs(packet->${header_name}.${field_name}) & ${hex(mask)}) >> ${bit_offset_hdr}) == ${hex(byte_array_to_int(value))} \
//::                  else:
        ntohs(packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(value))} \
//::                  #endif
//::                elif bit_width == 32:
//::                  if mask:
        ((ntohl(packet->${header_name}.${field_name}) & ${hex(mask)}) >> ${bit_offset_hdr}) == ${hex(byte_array_to_int(value))} \
//::                  else:
        ntohl(packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(value))} \
//::                  #endif
//::                elif bit_width == 64:
//::                  if mask:
        ((nothll(packet->${header_name}.${field_name}) & ${hex(mask)}) >> ${bit_offset_hdr}) == ${hex(byte_array_to_int(value))} \
//::                  else:
        ntohll(packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(value))} \
//::                  #endif
//::                elif bit_width <= 64:
//::                  if mask:
        (be${bit_width}_to_u64((const uint8_t *) &packet->${header_name}.${field_name}) & ${hex(mask)}) >> ${bit_offset_hdr} == ${hex(byte_array_to_int(value))} \
//::                  else:
        be${bit_width}_to_u64((const uint8_t *) &packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(value))} \
//::                  #endif
//::                  # TODO: right now only covers up to 64 bits, look into how to extend this range.
//::                else:
//::                  assert(False)
//::                #endif
//::              elif key_type == "current":
//::                bit_offset, bit_width = key_value
//::                # TODO: implement this.
//::              else:
//::                pass  # TODO: implement this.
//::              #endif
//::              break  # TODO: look into how to handle multiple control variables.
//::            #endfor
        && true) \
    { \
//::            if next_state[0] == "parse_state":
        OVS_MINIFLOW__${next_state[1].upper()} \
//::            elif next_state[0] == "table" or next_state[0] == "conditional_table":
        OVS_MINIFLOW_OUT \
//::            else:
//::              assert(False)
//::            #endif
    } \
//::          elif case_type == "default":
//::            if next_state[0] == "parse_state":
    OVS_MINIFLOW__${next_state[1].upper()} \
//::            elif next_state[0] == "table" or next_state[0] == "conditional_table":
    OVS_MINIFLOW_OUT \
//::            else:
//::              assert(False)
//::            #endif
//::          else:
//::            assert(False)  # TODO: implement this.
//::          #endif
//::        #endif
//::      #endfor
//::    else:
//::      assert(False)
//::    #endif

//::  #endfor
#define OVS_MINIFLOW_OUT \
    packet->payload_ofs = (char *)data - l2; \
//:: for header_name in ordered_header_instances_metadata:
//::   if header_name == "standard_metadata":
//::     continue
//::   #endif
    if (is_${header_name}_touched) \
    { \
        miniflow_push_words(mf, ${header_name}, ${header_name}, \
            sizeof(struct ${header_name}_padded_header) / sizeof(uint64_t)); \
    } \
//:: #endfor
    goto out; \
    \

/* -- Called in lib/flow.c -- */
#define OVS_FLOW_WC_MAP \
//::  for header_name in ordered_header_instances_regular:
    FLOWMAP_SET(map, ${header_name}); \
//::  #endfor
    \

#endif	/* OVS_MATCH_FLOW_H */