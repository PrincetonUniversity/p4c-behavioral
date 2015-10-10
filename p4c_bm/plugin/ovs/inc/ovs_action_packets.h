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
 * File:   ovs_action_packets.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_PACKETS_H
#define	OVS_ACTION_PACKETS_H 1

//::  import math
//::
//::  ordered_field_instances_all__name_width = []
//::  ordered_header_instances_all_field__name_width = {}
//::  for header_name in ordered_header_instances_all:
//::    ordered_header_instances_all_field__name_width[header_name] = []
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
//::      ordered_field_instances_all__name_width += [(field_name, bit_width)]
//::      ordered_header_instances_all_field__name_width[header_name] += [(field_name, bit_width)]
//::    #endfor
//::  #endfor
//::
/* -- Called in lib/packets.h -- */
#define OVS_FUNC_DECLS \
    \

/* -- Called in lib/packets.c -- */
#define OVS_FUNC_DEFS \
    \

/* -- Called in lib/packets.c -- */
#define OVS_ADD_HEADER_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: \
        packet->${header_name}_valid = true; \
        break; \
    \
//::  #endfor

/* -- Called in lib/packets.c -- */
#define OVS_REMOVE_HEADER_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: \
        packet->${header_name}_valid = false; \
        packet->${header_name}_ofs = UINT16_MAX; \
        break; \
    \
//::  #endfor

/* -- Called in lib/packets.c -- */
#define OVS_DEPARSE_NEW_PAYLOAD_OFS \
//::  for header_name in ordered_header_instances_regular:
    if (packet->${header_name}_valid) { \
        new_payload_ofs += sizeof(struct ${header_name}_header); \
    } \
//::  #endfor
    \

/* -- Called in lib/packets.c -- */
#define OVS_DEPARSE_WRITE_HEADERS \
//::  for header_name in ordered_header_instances_regular:
    if (packet->${header_name}_valid) { \
        memcpy(data + run_ofs, &packet->${header_name}, sizeof(struct ${header_name}_header)); \
        packet->${header_name}_ofs = run_ofs; \
        \
        run_ofs += sizeof(struct ${header_name}_header); \
    } \
//::  #endfor
    \

#endif	/* OVS_ACTION_PACKETS_H */