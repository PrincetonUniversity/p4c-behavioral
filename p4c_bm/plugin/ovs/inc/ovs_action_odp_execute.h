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
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    static void \
    odp_execute_modify_field_${field_name}(struct dp_packet *packet, \
                            const struct nlattr *a) \
    { \
        const struct ovs_action_modify_field_${field_name} *oa = nl_attr_get(a); \
//::      if bit_width == 8 or bit_width == 16 or bit_width == 32 or bit_width == 64:
        packet->${header_name}.${field_name} = oa->value | (packet->${header_name}.${field_name} & ~oa->mask); \
//::      else:
        apply_mask((const uint8_t *) &oa->value, (const uint8_t *) &oa->mask, \
                   (uint8_t *) &packet->${header_name}.${field_name}, \
                   sizeof packet->${header_name}.${field_name}); \
//::      #endif
    } \
    \
//::    #endfor
//::  #endfor


/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ACTIONS_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
        for (i = 0; i < cnt; i++) { \
            add_header_${header_name}(packets[i]); \
        } \
        break; \
    case OVS_ACTION_ATTR_REMOVE_HEADER_${header_name.upper()}: \
        for (i = 0; i < cnt; i++) { \
            remove_header_${header_name}(packets[i]); \
        } \
        break; \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OVS_ACTION_ATTR_MODIFY_FIELD_${field_name.upper()}: \
        for (i = 0; i < cnt; i++) { \
            odp_execute_modify_field_${field_name}(packets[i], a); \
        } \
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_REQUIRES_DATAPATH_ASSISTANCE_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
    case OVS_ACTION_ATTR_REMOVE_HEADER_${header_name.upper()}: \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OVS_ACTION_ATTR_MODIFY_FIELD_${field_name.upper()}: \
//::    #endfor
//::  #endfor
        return false; \
    \

#endif	/* OVS_ACTION_ODP_EXECUTE_H */