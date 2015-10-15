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
 * File:   ovs_action_odp_execute.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_ODP_EXECUTE_H
#define	OVS_ACTION_ODP_EXECUTE_H 1

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
/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_FUNCS \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ACTIONS_CASES \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_REQUIRES_DATAPATH_ASSISTANCE_CASES \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ADD_TO_FIELD_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OVS_KEY_ATTR_${field_name.upper()}: { \
//::      if bit_width == 8:
        const uint8_t *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = \
                packet->${header_name}.${field_name} + *value; \
//::      elif bit_width == 16:
        const ovs_be16 *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = htons( \
                ntohs(packet->${header_name}.${field_name}) + ntohs(*value)); \
//::      elif bit_width == 32:
        const ovs_be32 *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = htonl( \
                ntohl(packet->${header_name}.${field_name}) + ntohl(*value)); \
//::      elif bit_width == 64:
        const ovs_be64 *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = u64_to_be64( \
                be64_to_u64(packet->${header_name}.${field_name}) + be64_to_u64(*value)); \
//::      else:
//::        pass  # TODO: handle this case.
//::      #endif
        break; \
    } \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_SUB_FROM_FIELD_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OVS_KEY_ATTR_${field_name.upper()}: { \
//::      if bit_width == 8:
        const uint8_t *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = \
                packet->${header_name}.${field_name} - *value; \
//::      elif bit_width == 16:
        const ovs_be16 *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = htons( \
                ntohs(packet->${header_name}.${field_name}) - ntohs(*value)); \
//::      elif bit_width == 32:
        const ovs_be32 *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = htonl( \
                ntohl(packet->${header_name}.${field_name}) - ntohl(*value)); \
//::      elif bit_width == 64:
        const ovs_be64 *value = nl_attr_get(a); \
        packet->${header_name}.${field_name} = u64_to_be64( \
                be64_to_u64(packet->${header_name}.${field_name}) - be64_to_u64(*value)); \
//::      else:
//::        pass  # TODO: handle this case.
//::      #endif
        break; \
    } \
//::    #endfor
//::  #endfor
    \

#endif	/* OVS_ACTION_ODP_EXECUTE_H */