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
 * File:   ovs_match_odp_execute.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_ODP_EXECUTE_H
#define	OVS_MATCH_ODP_EXECUTE_H 1

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
#define OVS_ODP_SET_ACTIONS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    odp_set_${header_name}(struct dp_packet *packet, const struct ovs_key_${header_name} *key, \
            const struct ovs_key_${header_name} *mask) \
    { \
        struct ${header_name}_header *${header_name} = &packet->${header_name}; \
        \
//::    # TODO: this condition should be indicated back to the user, look into this.
        if (${header_name}) { \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
//::      if bit_width == 8:
            uint8_t ${field_name} = key->${field_name} | (${header_name}->${field_name} & ~mask->${field_name}); \
//::      elif bit_width == 16:
            ovs_be16 ${field_name} = key->${field_name} | (${header_name}->${field_name} & ~mask->${field_name}); \
//::      elif bit_width == 32:
            ovs_be32 ${field_name} = key->${field_name} | (${header_name}->${field_name} & ~mask->${field_name}); \
//::      elif bit_width == 64:
            ovs_be64 ${field_name} = key->${field_name} | (${header_name}->${field_name} & ~mask->${field_name}); \
//::      else:
            uint8_t ${field_name}[${bit_width}/8]; \
            ovs_apply_mask(key->${field_name}, ${header_name}->${field_name}, mask->${field_name}, \
                ${field_name}, ${bit_width}/8); \
//::      #endif
//::    #endfor
            \
            packet_set_${header_name}( \
//::    for field_name, _ in ordered_header_instances_all_field__name_width[header_name]:
                ${field_name}, \
//::    #endfor
                packet); \
        } \
    } \
    \
//::  #endfor

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_SET_ACTION \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: \
        { \
            const struct ovs_key_${header_name} *${header_name}_key = \
                  nl_attr_get_unspec(a, sizeof(struct ovs_key_${header_name})); \
            packet_set_${header_name}( \
//::    for field_name, _ in ordered_header_instances_all_field__name_width[header_name]:
                ${header_name}_key->${field_name}, \
//::    #endfor
                packet); \
        } \
        break; \
//::  #endfor
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_MASKED_SET_ACTION \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: \
        odp_set_${header_name}(packet, nl_attr_get(a), \
                get_mask(a, struct ovs_key_${header_name})); \
        break; \
//::  #endfor
    \

#endif	/* OVS_MATCH_ODP_EXECUTE_H */