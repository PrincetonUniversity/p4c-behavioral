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

//::  import math
//::
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
//::      # TODO: implement parser implementation style 0 (i.e., non concatenated field parsing).
    OVS_MINIFLOW_OUT \
//::    elif OVS_PARSER_IMP == 1:
//::      # Note: handle call sequence ###
//::      call_sequence = parse_info["call_sequence"]
//::
//::      call_id = 0
//::      for call in call_sequence:
//::        type = call[0]
//::        if type == "extract":
//::          header_name = call[1]
    if (OVS_UNLIKELY(size < sizeof(struct ${header_name}_header))) \
        OVS_MINIFLOW_OUT \
    packet->${header_name}_ofs = ((char *) data) - l2; \
    struct ${header_name}_padded_header *${header_name}_${call_id} = (struct ${header_name}_padded_header *) data_pull(&data, &size, \
        sizeof(struct ${header_name}_header)); \
//::          # NOTE: this valid is used by the slow-path
    ${header_name}_${call_id}->${header_name}_valid = 1; \
//::          # TODO: offset increase should be based on header length expression, need to implement this.
    miniflow_push_words(mf, ${header_name}, ${header_name}_${call_id}, \
        sizeof(struct ${header_name}_padded_header) / sizeof(uint64_t)); \
    packet->${header_name} = *(struct ${header_name}_header *) ${header_name}_${call_id}; \
//::          # NOTE: this valid is used by the fast(data)-path
    packet->${header_name}_valid = 1; \
    \
//::        elif type == "set":
//::          destination = call[1]
//::
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
    ${metadata_name}.hdr.${aligned_metadata_name} = ((uint8_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = htons(((uint16_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr}) \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~htons(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonl(((uint32_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr}) \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~htonl(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonll(((uint64_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr}) \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~htonll(${hex(aligned_metadata_mask)})); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            else:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = (uint8_t) ${source_value}; \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = htons((uint16_t) ${source_value}); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t) ${source_value}); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t) ${source_value}); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            #endif
//::          elif source_type == "latest":
//::            source = call[3]
//::
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
    uint8_t value1_${call_id} = (packet->${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = (ntohs(packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = (ntohl(packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = (ntohll(packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              else:
//::                if aligned_field_bit_width == 8:
    uint8_t value1_${call_id} = packet->${header_name}.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = ntohs(packet->${header_name}.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = ntohl(packet->${header_name}.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = ntohll(packet->${header_name}.${aligned_field_name}); \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              #endif
//::            elif header_name in ordered_header_instances_metadata:
//::              if aligned_field_mask:
//::                if aligned_field_bit_width == 8:
    uint8_t value1_${call_id} = (${metadata_name}.hdr.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = (ntohs(${metadata_name}.hdr.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = (nothl(${metadata_name}.hdr.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = (ntohll(${metadata_name}.hdr.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              else:
//::                if aligned_field_bit_width == 8:
    uint8_t value1_${call_id} = ${metadata_name}.hdr.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = ntohs(${metadata_name}.hdr.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = ntohl(${metadata_name}.hdr.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = ntohll(${metadata_name}.hdr.${aligned_field_name}); \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              #endif
//::            else:
//::              assert(False)
//::            #endif
//::
//::            if aligned_metadata_mask:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = ((uint8_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr} \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = htons(((uint16_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr}) \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~htons(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr}) \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~htonl(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr}) \
        | (${metadata_name}.hdr.${aligned_metadata_name} & ~htonll(${hex(aligned_metadata_mask)})); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            else:
//::              if aligned_metadata_bit_width == 8:
    ${metadata_name}.hdr.${aligned_metadata_name} = (uint8_t) value1_${call_id}; \
//::              elif aligned_metadata_bit_width == 16:
    ${metadata_name}.hdr.${aligned_metadata_name} = htons((uint16_t) value1_${call_id}); \
//::              elif aligned_metadata_bit_width == 32:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t) value1_${call_id}); \
//::              elif aligned_metadata_bit_width == 64:
    ${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t) value1_${call_id}); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            #endif
//::          else:
//::            assert(False)  # TODO: handle this case (e.g., current() etc).
//::          #endif
    is_${metadata_name}_touched = true; \
    \
//::        else:
//::          assert(False)
//::        #endif
//::      #endfor
//::
//::      # Note: handle state transitions ###
//::      branch_on = parse_info['branch_on']
//::      branch_to = parse_info['branch_to']
//::
//::      for case in branch_to:
//::        case_type, case_value, case_mask, case_next_state = case
//::        if not branch_on:
//::          assert(len(branch_to) == 1)
//::          if case_next_state[0] == "parse_state":
    OVS_MINIFLOW__${case_next_state[1].upper()} \
//::          elif case_next_state[0] == "table" or case_next_state[0] == "conditional_table":
    OVS_MINIFLOW_OUT \
//::          else:
//::            assert(False)  # TODO: handle this case (i.e., for parser exceptions).
//::          #endif
//::        else:
//::          if case_type == "value":
    if ( \
//::            key_id = 0
//::            for key_type, key_value in branch_on:
//::              if key_type == "field_ref":
//::                header_name = field_info[key_value]["parent_header"]
//::                aligned_field_name = aligned_field_info[key_value]["name"]
//::                aligned_field_bit_width = aligned_field_info[key_value]["bit_width"]
//::                aligned_field_mask = aligned_field_info[key_value]["mask"]
//::                aligned_field_bit_offset_hdr = aligned_field_info[key_value]["bit_offset_hdr"]
//::
//::                if aligned_field_bit_width == 8:
//::                  if aligned_field_mask:
        (((packet->${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  else:
        (packet->${header_name}.${aligned_field_name} == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_field_bit_width == 16:
//::                  if aligned_field_mask:
        (((ntohs(packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  else:
        (ntohs(packet->${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_field_bit_width == 32:
//::                  if aligned_field_mask:
        (((ntohl(packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  else:
        (ntohl(packet->${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_field_bit_width == 64:
//::                  if aligned_field_mask:
        (((nothll(packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}) && \
//::                  else:
        (ntohll(packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}) && \
//::                  #endif
//::                  key_id += 8
//::                elif aligned_field_bit_width <= 64:
//::                  if aligned_field_mask:
        ((be${aligned_field_bit_width}_to_u64((const uint8_t *) &packet->${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_bit_offset_hdr} == ${hex(byte_array_to_int(case_value[key_id:key_id+(aligned_field_bit_width/8)]))}) && \
//::                  else:
        (be${aligned_field_bit_width}_to_u64((const uint8_t *) &packet->${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+(aligned_field_bit_width/8)]))}) && \
//::                  #endif
//::                  key_id += aligned_field_bit_width/8
//::                else:
//::                  assert(False)  # TODO: right now only covers up to 64 bits, look into how to extend this range.
//::                #endif
//::              elif key_type == "current":
//::                key_bit_offset, key_bit_width = key_value
//::
//::                aligned_key_bit_base_offset = int(key_bit_offset/8)*8
//::                adjusted_key_bit_base_offset = key_bit_offset - aligned_key_bit_base_offset
//::                aligned_key_bit_width = int(math.ceil((adjusted_key_bit_base_offset+key_bit_width)/8.0)*8)
//::                aligned_key_bit_offset_hdr = aligned_key_bit_width - ((adjusted_key_bit_base_offset%aligned_key_bit_width) + key_bit_width)
//::                aligned_key_mask = ((1 << key_bit_width) - 1) << aligned_key_bit_offset_hdr
//::                aligned_key_mask = 0 if (((1 << aligned_key_bit_width) - 1) == aligned_key_mask) else aligned_key_mask
//::
//::                if aligned_key_bit_width == 8:
//::                  if aligned_key_mask:
        ((((*(uint8_t *) (((char *) data) + ${aligned_key_bit_base_offset/8})) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  else:
        ((*(uint8_t *) (((char *) data) + ${aligned_key_bit_base_offset/8})) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_key_bit_width == 16:
//::                  if aligned_key_mask:
        (((ntohs((*(ovs_be16 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  else:
        (ntohs((*(ovs_be16 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_key_bit_width == 32:
//::                  if aligned_key_mask:
        (((ntohl((*(ovs_be32 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  else:
        (ntohl((*(ovs_be32 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}) && \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_key_bit_width == 64:
//::                  if aligned_key_mask:
        (((ntohl((*(ovs_be64 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}) && \
//::                  else:
        (ntohl((*(ovs_be64 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}) && \
//::                  #endif
//::                  key_id += 8
//::                else:
//::                  assert(False)  # TODO: right now only covers up to 64 bits, look into how to extend this range.
//::                #endif
//::              else:
//::                assert(False)
//::              #endif
//::            #endfor
        true) \
//::          elif case_type == "default":
//::            pass
//::          else:
//::            assert(False)
//::          #endif
    { \
//::          if case_next_state[0] == "parse_state":
        OVS_MINIFLOW__${case_next_state[1].upper()} \
//::          elif case_next_state[0] == "table" or case_next_state[0] == "conditional_table":
        OVS_MINIFLOW_OUT \
//::          else:
//::            assert(False)
//::          #endif
    } \
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
        miniflow_push_words(mf, ${header_name}, &${header_name}, \
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