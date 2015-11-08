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
 * File:   ovs_match_packets.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_PACKETS_H
#define	OVS_MATCH_PACKETS_H 1

//::  import math
//::
//::  ordered_field_instances_non_virtual__name_width = []
//::  ordered_header_instances_non_virtual_field__name_width = {}
//::  for header_name in ordered_header_instances_non_virtual:
//::    ordered_header_instances_non_virtual_field__name_width[header_name] = []
//::    proc_fields = []
//::    for field_name in header_info[header_name]["fields"]:
//::      if OVS_PARSER_IMP == 0:
//::        bit_width = field_info[field_name]["bit_width"]
//::        bit_width = int(math.ceil(bit_width/8.0)*8)
//::      elif OVS_PARSER_IMP == 1:
//::        bit_width = aligned_field_info[field_name]["bit_width"]
//::        field_name = aligned_field_info[field_name]["name"]
//::        if field_name in proc_fields:
//::          continue
//::        #endif
//::        proc_fields += [field_name]
//::      else:
//::        assert(False)
//::      #endif
//::      ordered_field_instances_non_virtual__name_width += [(field_name, bit_width)]
//::      ordered_header_instances_non_virtual_field__name_width[header_name] += [(field_name, bit_width)]
//::    #endfor
//::  #endfor
//::
/* -- Called in lib/packets.h -- */
//::  for header_name in ordered_header_instances_non_virtual:
//::    if header_name == "standard_metadata":
//::      pass
//::    else:
//::      header_len = sum([bit_width for _, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]])/8
#define ${header_name.upper()}_HEADER_LEN ${header_len}
//::    #endif
//::  #endfor

/* -- Called in lib/packets.h -- */
#define OVS_HDR_STRUCTS \
//::  for header_name in ordered_header_instances_non_virtual:
//::    if header_name == "standard_metadata":
//::      continue
//::    #endif
//::    run_bit_width = 0
    OVS_PACKED( \
    struct ${header_name}_header { \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 8:
        uint8_t ${field_name}; \
//::      elif bit_width == 16:
        ovs_be16 ${field_name}; \
//::      elif bit_width == 32:
        ovs_be32 ${field_name}; \
//::      elif bit_width == 64:
        ovs_be64 ${field_name}; \
//::      else:
        struct ${field_name}_t ${field_name}; \
//::      #endif
//::      run_bit_width += bit_width
//::    #endfor
    }); \
    BUILD_ASSERT_DECL(${header_name.upper()}_HEADER_LEN == sizeof(struct ${header_name}_header)); \
    \
    OVS_PACKED( \
    struct ${header_name}_padded_header { \
        struct ${header_name}_header hdr; \
//::    valid_byte = 0
//::    if header_name in ordered_header_instances_regular:
        uint8_t ${header_name}_valid; \
//::      run_bit_width += 8
//::      valid_byte = 1
//::    #endif
//::
//::    pad_bits = 64 - (run_bit_width % 64)
//::    pad_bytes = 0
//::    if pad_bits < 64:
//::      pad_bytes = pad_bits/8
        uint8_t pad[${pad_bytes}]; \
//::    #endif
    }); \
    BUILD_ASSERT_DECL( \
        ${header_name.upper()}_HEADER_LEN+${valid_byte}+${pad_bytes} == sizeof(struct ${header_name}_padded_header)); \
    \
//::  #endfor

/* -- Called in lib/packets.h -- */
#define OVS_HDR_DECLS \
//::  for header_name in ordered_header_instances_regular:
    void packet_set_${header_name}( \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 8:
        uint8_t ${field_name}, \
//::      elif bit_width == 16:
        ovs_be16 ${field_name}, \
//::      elif bit_width == 32:
        ovs_be32 ${field_name}, \
//::      elif bit_width == 64:
        ovs_be64 ${field_name}, \
//::      else:
        struct ${field_name}_t ${field_name}, \
//::      #endif
//::    #endfor
        uint8_t ${header_name}_valid, \
        struct dp_packet *packet); \
    \
//::  #endfor

/* -- Called in lib/packets.c -- */
#define OVS_HDR_DEFS \
//::  for header_name in ordered_header_instances_regular:
    void packet_set_${header_name}( \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 8:
        uint8_t ${field_name}, \
//::      elif bit_width == 16:
        ovs_be16 ${field_name}, \
//::      elif bit_width == 32:
        ovs_be32 ${field_name}, \
//::      elif bit_width == 64:
        ovs_be64 ${field_name}, \
//::      else:
        struct ${field_name}_t ${field_name}, \
//::      #endif
//::    #endfor
        uint8_t ${header_name}_valid, \
        struct dp_packet *packet) \
    { \
        struct ${header_name}_header *${header_name} = &packet->${header_name}; \
        \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
        ${header_name}->${field_name} = ${field_name}; \
//::    #endfor
        packet->${header_name}_valid = ${header_name}_valid; \
    } \
    \
//:: #endfor

#endif	/* OVS_MATCH_PACKETS_H */