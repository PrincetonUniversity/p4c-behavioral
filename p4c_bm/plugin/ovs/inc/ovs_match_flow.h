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
    struct _${header_name}_padded_header _${header_name}; \
//::  #endfor
    struct valid_padded_header valid; \
    \

/* -- Called in lib/flow.c -- */
#define OVS_MINIFLOW_EXTRACT_METADATA_DEFS \
//::  for header_name in ordered_header_instances_metadata:
//::    if header_name == "standard_metadata":
//::      continue
//::    #endif
    struct _${header_name}_padded_header _${header_name}; \
    bool is__${header_name}_header_touched = false; \
    \
//::  #endfor
    struct valid_padded_header valid; \
    \

/* -- Called in lib/flow.c -- */
#define OVS_MINIFLOW_EXTRACT \
    { \
        OVS_MINIFLOW__START \
    } \
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
    if (OVS_UNLIKELY(size < sizeof(struct _${header_name}_header))) \
    { \
        OVS_MINIFLOW_OUT \
    } \
    \
    packet->_${header_name}_ofs = ((char *) data) - l2; \
    struct _${header_name}_padded_header *_${header_name}_${call_id} = (struct _${header_name}_padded_header *) data_pull(&data, &size, \
        sizeof(struct _${header_name}_header)); \
//::          # TODO: offset increase should be based on header length expression, need to implement this.
    miniflow_push_words(mf, _${header_name}, _${header_name}_${call_id}, \
        sizeof(struct _${header_name}_padded_header) / sizeof(uint64_t)); \
    packet->_${header_name} = *(struct _${header_name}_header *) _${header_name}_${call_id}; \
    packet->_${header_name}_valid = valid.hdr._${header_name}_valid = 1; \
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
    _${metadata_name}.hdr.${aligned_metadata_name} = ((uint8_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr} \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 16:
    _${metadata_name}.hdr.${aligned_metadata_name} = htons(((uint16_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr}) \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~htons(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 32:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonl(((uint32_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr}) \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~htonl(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 64:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonll(((uint64_t) ${source_value}) << ${aligned_metadata_bit_offset_hdr}) \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~htonll(${hex(aligned_metadata_mask)})); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            else:
//::              if aligned_metadata_bit_width == 8:
    _${metadata_name}.hdr.${aligned_metadata_name} = (uint8_t) ${source_value}; \
//::              elif aligned_metadata_bit_width == 16:
    _${metadata_name}.hdr.${aligned_metadata_name} = htons((uint16_t) ${source_value}); \
//::              elif aligned_metadata_bit_width == 32:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t) ${source_value}); \
//::              elif aligned_metadata_bit_width == 64:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t) ${source_value}); \
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
    uint8_t value1_${call_id} = (packet->_${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = (ntohs(packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = (ntohl(packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = (ntohll(packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              else:
//::                if aligned_field_bit_width == 8:
    uint8_t value1_${call_id} = packet->_${header_name}.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = ntohs(packet->_${header_name}.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = ntohl(packet->_${header_name}.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = ntohll(packet->_${header_name}.${aligned_field_name}); \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              #endif
//::            elif header_name in ordered_header_instances_metadata:
//::              if aligned_field_mask:
//::                if aligned_field_bit_width == 8:
    uint8_t value1_${call_id} = (_${metadata_name}.hdr.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = (ntohs(_${metadata_name}.hdr.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = (nothl(_${metadata_name}.hdr.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = (ntohll(_${metadata_name}.hdr.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}; \
//::                else:
//::                  assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::                #endif
//::              else:
//::                if aligned_field_bit_width == 8:
    uint8_t value1_${call_id} = _${metadata_name}.hdr.${aligned_field_name}; \
//::                elif aligned_field_bit_width == 16:
    uint16_t value1_${call_id} = ntohs(_${metadata_name}.hdr.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 32:
    uint32_t value1_${call_id} = ntohl(_${metadata_name}.hdr.${aligned_field_name}); \
//::                elif aligned_field_bit_width == 64:
    uint64_t value1_${call_id} = ntohll(_${metadata_name}.hdr.${aligned_field_name}); \
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
    _${metadata_name}.hdr.${aligned_metadata_name} = ((uint8_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr} \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~${hex(aligned_metadata_mask)}); \
//::              elif aligned_metadata_bit_width == 16:
    _${metadata_name}.hdr.${aligned_metadata_name} = htons(((uint16_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr}) \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~htons(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 32:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr}) \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~htonl(${hex(aligned_metadata_mask)})); \
//::              elif aligned_metadata_bit_width == 64:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t) value1_${call_id}) << ${aligned_metadata_bit_offset_hdr}) \
        | (_${metadata_name}.hdr.${aligned_metadata_name} & ~htonll(${hex(aligned_metadata_mask)})); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            else:
//::              if aligned_metadata_bit_width == 8:
    _${metadata_name}.hdr.${aligned_metadata_name} = (uint8_t) value1_${call_id}; \
//::              elif aligned_metadata_bit_width == 16:
    _${metadata_name}.hdr.${aligned_metadata_name} = htons((uint16_t) value1_${call_id}); \
//::              elif aligned_metadata_bit_width == 32:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonl((uint32_t) value1_${call_id}); \
//::              elif aligned_metadata_bit_width == 64:
    _${metadata_name}.hdr.${aligned_metadata_name} = htonll((uint64_t) value1_${call_id}); \
//::              else:
//::                assert(False)  # TODO: handle this case (for arbitrary byte combinations).
//::              #endif
//::            #endif
//::          else:
//::            assert(False)  # TODO: handle this case (e.g., current() etc).
//::          #endif
    is__${metadata_name}_header_touched = true; \
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
//::      case_id = 0
//::      for case in branch_to:
//::        case_type, case_value, case_mask, case_next_state = case
//::        if not branch_on:
//::          assert(len(branch_to) == 1)
    { \
//::          if case_next_state[0] == "parse_state":
        OVS_MINIFLOW__${case_next_state[1].upper()} \
//::          elif case_next_state[0] == "table" or case_next_state[0] == "conditional_table":
        OVS_MINIFLOW_OUT \
//::          else:
//::            assert(False)  # TODO: handle this case (i.e., for parser exceptions).
//::          #endif
    } \
    \
//::        else:
//::          if case_type == "value":
//::            branch_id = 0
//::            key_id = 0
//::            for key_type, key_value in branch_on:
//::              if key_type == "field_ref":
//::                header_name = field_info[key_value]["parent_header"]
//::                aligned_field_name = aligned_field_info[key_value]["name"]
//::                aligned_field_bit_width = aligned_field_info[key_value]["bit_width"]
//::                aligned_field_mask = aligned_field_info[key_value]["mask"]
//::                aligned_field_bit_offset_hdr = aligned_field_info[key_value]["bit_offset_hdr"]
//::
//::                if header_name in ordered_header_instances_regular:
//::                  if aligned_field_bit_width == 8:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((packet->_${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (packet->_${header_name}.${aligned_field_name} == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    #endif
//::                    key_id += 4
//::                  elif aligned_field_bit_width == 16:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((ntohs(packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (ntohs(packet->_${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    #endif
//::                    key_id += 4
//::                  elif aligned_field_bit_width == 32:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((ntohl(packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (ntohl(packet->_${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    #endif
//::                    key_id += 4
//::                  elif aligned_field_bit_width == 64:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((nothll(packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (ntohll(packet->_${header_name}.${field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}); \
//::                    #endif
//::                    key_id += 8
//::                  elif aligned_field_bit_width <= 64:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = ((be${aligned_field_bit_width}_to_u64((const uint8_t *) &packet->_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr} == ${hex(byte_array_to_int(case_value[key_id:key_id+(aligned_field_bit_width/8)]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (be${aligned_field_bit_width}_to_u64((const uint8_t *) &packet->_${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+(aligned_field_bit_width/8)]))}); \
//::                    #endif
//::                    key_id += aligned_field_bit_width/8
//::                  else:
//::                    assert(False)  # TODO: right now only covers up to 64 bits, look into how to extend this range.
//::                  #endif
//::                elif header_name in ordered_header_instances_metadata:
//::                  if aligned_field_bit_width == 8:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((_${header_name}.${aligned_field_name} & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (_${header_name}.${aligned_field_name} == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    #endif
//::                    key_id += 4
//::                  elif aligned_field_bit_width == 16:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((ntohs(_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (ntohs(_${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    #endif
//::                    key_id += 4
//::                  elif aligned_field_bit_width == 32:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((ntohl(_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (ntohl(_${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                    #endif
//::                    key_id += 4
//::                  elif aligned_field_bit_width == 64:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = (((nothll(_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (ntohll(_${header_name}.${field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}); \
//::                    #endif
//::                    key_id += 8
//::                  elif aligned_field_bit_width <= 64:
//::                    if aligned_field_mask:
    bool check_${case_id}_${branch_id} = ((be${aligned_field_bit_width}_to_u64((const uint8_t *) &_${header_name}.${aligned_field_name}) & ${hex(aligned_field_mask)}) >> ${aligned_field_bit_offset_hdr} == ${hex(byte_array_to_int(case_value[key_id:key_id+(aligned_field_bit_width/8)]))}); \
//::                    else:
    bool check_${case_id}_${branch_id} = (be${aligned_field_bit_width}_to_u64((const uint8_t *) &_${header_name}.${aligned_field_name}) == ${hex(byte_array_to_int(case_value[key_id:key_id+(aligned_field_bit_width/8)]))}); \
//::                    #endif
//::                    key_id += aligned_field_bit_width/8
//::                  else:
//::                    assert(False)  # TODO: right now only covers up to 64 bits, look into how to extend this range.
//::                  #endif
//::                #endif
//::              elif key_type == "current":
//::                key_bit_offset, key_bit_width = key_value
//::
//::                aligned_key_bit_base_offset = int(key_bit_offset/8)*8
//::                adjusted_key_bit_offset = key_bit_offset - aligned_key_bit_base_offset
//::                aligned_key_bit_width = int(math.ceil((adjusted_key_bit_offset+key_bit_width)/8.0)*8)
//::                aligned_key_bit_offset_hdr = aligned_key_bit_width - ((adjusted_key_bit_offset%aligned_key_bit_width) + key_bit_width)
//::                aligned_key_mask = ((1 << key_bit_width) - 1) << aligned_key_bit_offset_hdr
//::                aligned_key_mask = 0 if (((1 << aligned_key_bit_width) - 1) == aligned_key_mask) else aligned_key_mask
    if (OVS_UNLIKELY(size < (${aligned_key_bit_base_offset/8}+${aligned_key_bit_width/8}))) \
    { \
        OVS_MINIFLOW_OUT \
    } \
    \
//::
//::                if aligned_key_bit_width == 8:
//::                  if aligned_key_mask:
    bool check_${case_id}_${branch_id} = ((((*(uint8_t *) (((char *) data) + ${aligned_key_bit_base_offset/8})) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                  else:
    bool check_${case_id}_${branch_id} = ((*(uint8_t *) (((char *) data) + ${aligned_key_bit_base_offset/8})) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_key_bit_width == 16:
//::                  if aligned_key_mask:
    bool check_${case_id}_${branch_id} = (((ntohs((*(ovs_be16 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                  else:
    bool check_${case_id}_${branch_id} = (ntohs((*(ovs_be16 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_key_bit_width == 32:
//::                  if aligned_key_mask:
    bool check_${case_id}_${branch_id} = (((ntohl((*(ovs_be32 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                  else:
    bool check_${case_id}_${branch_id} = (ntohl((*(ovs_be32 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) == ${hex(byte_array_to_int(case_value[key_id:key_id+4]))}); \
//::                  #endif
//::                  key_id += 4
//::                elif aligned_key_bit_width == 64:
//::                  if aligned_key_mask:
    bool check_${case_id}_${branch_id} = (((ntohl((*(ovs_be64 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) & ${hex(aligned_key_mask)}) >> ${aligned_key_bit_offset_hdr}) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}); \
//::                  else:
    bool check_${case_id}_${branch_id} = (ntohl((*(ovs_be64 *) (((char *) data) + ${aligned_key_bit_base_offset/8}))) == ${hex(byte_array_to_int(case_value[key_id:key_id+8]))}); \
//::                  #endif
//::                  key_id += 8
//::                else:
//::                  assert(False)  # TODO: right now only covers up to 64 bits, look into how to extend this range.
//::                #endif
//::              else:
//::                assert(False)
//::              #endif
//::              branch_id += 1
//::            #endfor
    if ( \
//::            branch_id = 0
//::            for key_type, key_value in branch_on:
        check_${case_id}_${branch_id} && \
//::              branch_id += 1
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
    \
//::        #endif
//::        case_id += 1
//::      #endfor
//::    else:
//::      assert(False)
//::    #endif

//::  #endfor
#define OVS_MINIFLOW_OUT \
    packet->payload_ofs = (char *)data - l2; \
    \
//:: for header_name in ordered_header_instances_metadata:
//::   if header_name == "standard_metadata":
//::     continue
//::   #endif
    if (is__${header_name}_header_touched) \
    { \
        miniflow_push_words(mf, _${header_name}, &_${header_name}, \
            sizeof(struct _${header_name}_padded_header) / sizeof(uint64_t)); \
    } \
//:: #endfor
    \
    miniflow_push_words(mf, valid, &valid, \
            sizeof(struct valid_padded_header) / sizeof(uint64_t)); \
    goto out; \
    \

/* -- Called in lib/flow.c -- */
#define OVS_FLOW_WC_MAP \
//::  for header_name in ordered_header_instances_non_virtual:
//::   if header_name == "standard_metadata":
//::     continue
//::   #endif
    FLOWMAP_SET(map, _${header_name}); \
//::  #endfor
    FLOWMAP_SET(map, valid); \
    \

#endif	/* OVS_MATCH_FLOW_H */