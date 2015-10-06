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
//::  for header_name in ordered_header_instances_all:
    struct ${header_name}_padded_header ${header_name}; \
//::  #endfor
    \

/* -- Called in lib/flow.c -- */
#define OVS_MINIFLOW_EXTRACT \
    OVS_MINIFLOW__START \
    \

//::  for state, parse_info in parse_states.items():
#define OVS_MINIFLOW__${state.upper()} \
//::    if OVS_PARSER_IMP == 0:
    OVS_MINIFLOW_OUT \
//::    elif OVS_PARSER_IMP == 1:
//::      call_sequence = parse_info['call_sequence']
//::      for type, header_name in call_sequence:
//::        if type == 'extract':
    packet->${header_name}_ofs = (char *)data - l2; \
    \
    struct ${header_name}_padded_header *${header_name}; \
    ${header_name} = (struct ${header_name}_padded_header *) data_pull(&data, &size, \
        sizeof(struct ${header_name}_header)); \
//:: # TODO: offset increase should be based on header length expression, look into this.
    miniflow_push_words(mf, ${header_name}, ${header_name}, \
        sizeof(struct ${header_name}_padded_header) / sizeof(uint64_t)); \
    \
    packet->${header_name} = *(struct ${header_name}_header *) ${header_name}; \
    packet->${header_name}_valid = true; \
    \
//::        else:
//::          assert(False)
//::        #endif
//::      #endfor
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
        ((be64_to_u64(packet->${header_name}.${field_name}) & ${hex(mask)}) >> ${bit_offset_hdr}) == ${hex(byte_array_to_int(value))} \
//::                  else:
        be64_to_u64(packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(value))} \
//::                  #endif
//::                elif bit_width <= 64:
//::                  if mask:
        (be_to_u64(packet->${header_name}.${field_name}) & ${hex(mask)}) >> ${bit_offset_hdr} == ${hex(byte_array_to_int(value))} \
//::                  else:
        be_to_u64(packet->${header_name}.${field_name}) == ${hex(byte_array_to_int(value))} \
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
    goto out; \
    \

/* -- Called in lib/flow.c -- */
#define OVS_FLOW_WC_MAP \
//::  for header_name in ordered_header_instances_regular:
    FLOWMAP_SET(map, ${header_name}); \
//::  #endfor
    \

#endif	/* OVS_MATCH_FLOW_H */