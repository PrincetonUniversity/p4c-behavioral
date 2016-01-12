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
/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_SET_ACTION_FUNCS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    odp_set__${header_name}(struct dp_packet *packet, const struct ovs_key__${header_name} *key, \
            const struct ovs_key__${header_name} *mask) \
    { \
        struct _${header_name}_header *_${header_name} = &packet->_${header_name}; \
        \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 8:
        uint8_t ${field_name} = key->${field_name} | (_${header_name}->${field_name} & ~mask->${field_name}); \
//::      elif bit_width == 16:
        ovs_be16 ${field_name} = key->${field_name} | (_${header_name}->${field_name} & ~mask->${field_name}); \
//::      elif bit_width == 32:
        ovs_be32 ${field_name} = key->${field_name} | (_${header_name}->${field_name} & ~mask->${field_name}); \
//::      elif bit_width == 64:
        ovs_be64 ${field_name} = key->${field_name} | (_${header_name}->${field_name} & ~mask->${field_name}); \
//::      else:
        struct ${field_name}_t ${field_name}; \
        apply_mask_1((const uint8_t *) &key->${field_name}, (const uint8_t *) &_${header_name}->${field_name}, \
                     (const uint8_t *) &mask->${field_name}, \
                     (uint8_t *) &${field_name}, sizeof(struct ${field_name}_t)); \
//::      #endif
//::    #endfor
        \
        packet_set__${header_name}( \
//::    for field_name, _ in ordered_header_instances_non_virtual_field__name_width[header_name]:
            ${field_name}, \
//::    #endfor
            packet); \
    } \
    \
//::  #endfor
    static void \
    odp_set_valid(struct dp_packet *packet, const struct ovs_key_valid *key, \
                   const struct ovs_key_valid *mask) \
    { \
//::  for header_name in ordered_header_instances_regular:
        uint8_t _${header_name}_valid = key->_${header_name}_valid | (packet->_${header_name}_valid & ~mask->_${header_name}_valid); \
//::  #endfor
        \
        packet_set_valid( \
//::  for header_name in ordered_header_instances_regular:
            _${header_name}_valid, \
//::  #endfor
            packet); \
    } \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_SET_ACTION_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR__${header_name.upper()}: \
    { \
        const struct ovs_key__${header_name} *_${header_name}_key = \
            nl_attr_get_unspec(a, sizeof(struct ovs_key__${header_name})); \
        packet_set__${header_name}( \
//::    for field_name, _ in ordered_header_instances_non_virtual_field__name_width[header_name]:
            _${header_name}_key->${field_name}, \
//::    #endfor
            packet); \
        break; \
    } \
//::  #endfor
    case OVS_KEY_ATTR_VALID: \
    { \
        const struct ovs_key_valid *valid_key = \
            nl_attr_get_unspec(a, sizeof(struct ovs_key_valid)); \
        packet_set_valid( \
//::  for header_name in ordered_header_instances_regular:
            valid_key->_${header_name}_valid, \
//::  #endfor
            packet); \
        break; \
    } \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_MASKED_SET_ACTION_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR__${header_name.upper()}: \
        odp_set__${header_name}(packet, nl_attr_get(a), \
                get_mask(a, struct ovs_key__${header_name})); \
        break; \
//::  #endfor
    case OVS_KEY_ATTR_VALID: \
        odp_set_valid(packet, nl_attr_get(a), \
                       get_mask(a, struct ovs_key_valid)); \
        break; \
    \

#endif	/* OVS_MATCH_ODP_EXECUTE_H */
