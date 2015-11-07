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
 * File:   ovs_match_meta_flow.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_META_FLOW_H
#define	OVS_MATCH_META_FLOW_H 1

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
/* -- Called in lib/meta-flow.c -- */
#define OVS_GET_VALUE_CASES \
//::  for header_name in ordered_header_instances_non_virtual:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
//::      if bit_width == 8:
        value->u8 = flow->${header_name}.hdr.${field_name}; \
//::      elif bit_width == 16:
        value->be16 = flow->${header_name}.hdr.${field_name}; \
//::      elif bit_width == 32:
        value->be32 = flow->${header_name}.hdr.${field_name}; \
//::      elif bit_width == 64:
        value->be64 = flow->${header_name}.hdr.${field_name}; \
//::      else:
        memcpy(value->data, &flow->${header_name}.hdr.${field_name}, \
               sizeof flow->${header_name}.hdr.${field_name}); \
//::      #endif
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/meta-flow.c -- */
#define OVS_IS_VALUE_VALID_CASES \
//::  for field_name, _ in ordered_field_instances_non_virtual__name_width:
    case MFF_${field_name.upper()}: \
        return true; \
//::  #endfor
    \

/* -- Called in lib/meta-flow.c -- */
#define OVS_IS_ALL_WILD_CASES \
//::  for header_name in ordered_header_instances_non_virtual:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
//::      if bit_width == 8 or bit_width == 16 or bit_width == 32 or bit_width == 64:
        return !wc->masks.${header_name}.hdr.${field_name}; \
//::      else:
        return is_all_zeros(&wc->masks.${header_name}.hdr.${field_name}, \
                            sizeof wc->masks.${header_name}.hdr.${field_name}); \
//::      #endif
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/meta-flow.c -- */
#define OVS_SET_FLOW_VALUE_CASES \
//::  for header_name in ordered_header_instances_non_virtual:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
//::      if bit_width == 8:
        flow->${header_name}.hdr.${field_name} = value->u8; \
//::      elif bit_width == 16:
        flow->${header_name}.hdr.${field_name} = value->be16; \
//::      elif bit_width == 32:
        flow->${header_name}.hdr.${field_name} = value->be32; \
//::      elif bit_width == 64:
        flow->${header_name}.hdr.${field_name} = value->be64; \
//::      else:
        memcpy(&flow->${header_name}.hdr.${field_name}, value->data, \
               sizeof flow->${header_name}.hdr.${field_name}); \
//::      #endif
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/meta-flow.c -- */
#define OVS_SET_VLAUE_CASES \
//::  for header_name in ordered_header_instances_non_virtual:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
//::      if bit_width == 8:
        match->wc.masks.${header_name}.hdr.${field_name} = 0xff; \
        match->flow.${header_name}.hdr.${field_name} = value->u8; \
//::      elif bit_width == 16:
        match->wc.masks.${header_name}.hdr.${field_name} = OVS_BE16_MAX; \
        match->flow.${header_name}.hdr.${field_name} = value->be16; \
//::      elif bit_width == 32:
        match->wc.masks.${header_name}.hdr.${field_name} = OVS_BE32_MAX; \
        match->flow.${header_name}.hdr.${field_name} = value->be32; \
//::      elif bit_width == 64:
        match->wc.masks.${header_name}.hdr.${field_name} = OVS_BE64_MAX; \
        match->flow.${header_name}.hdr.${field_name} = value->be64; \
//::      else:
        memset(&match->wc.masks.${header_name}.hdr.${field_name}, 0xff, \
               sizeof match->wc.masks.${header_name}.hdr.${field_name}); \
        memcpy(&match->flow.${header_name}.hdr.${field_name}, value->data, \
               sizeof match->flow.${header_name}.hdr.${field_name}); \
//::      #endif
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/meta-flow.c -- */
#define OVS_SET_WILD_CASES \
//::  for header_name in ordered_header_instances_non_virtual:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
//::      if bit_width == 8 or bit_width == 16 or bit_width == 32 or bit_width == 64:
        match->flow.${header_name}.hdr.${field_name} = 0; \
        match->wc.masks.${header_name}.hdr.${field_name} = 0; \
//::      else:
        memset(&match->flow.${header_name}.hdr.${field_name}, 0, \
               sizeof match->flow.${header_name}.hdr.${field_name}); \
        memset(&match->wc.masks.${header_name}.hdr.${field_name}, 0, \
               sizeof match->wc.masks.${header_name}.hdr.${field_name}); \
//::      #endif
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/meta-flow.c -- */
#define OVS_SET_CASES \
//::  for header_name in ordered_header_instances_non_virtual:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
//::      if bit_width == 8:
        match->flow.${header_name}.hdr.${field_name} = value->u8 & mask->u8; \
        match->wc.masks.${header_name}.hdr.${field_name} = mask->u8; \
//::      elif bit_width == 16:
        match->flow.${header_name}.hdr.${field_name} = value->be16 & mask->be16; \
        match->wc.masks.${header_name}.hdr.${field_name} = mask->be16; \
//::      elif bit_width == 32:
        match->flow.${header_name}.hdr.${field_name} = value->be32 & mask->be32; \
        match->wc.masks.${header_name}.hdr.${field_name} = mask->be32; \
//::      elif bit_width == 64:
        match->flow.${header_name}.hdr.${field_name} = value->be64 & mask->be64; \
        match->wc.masks.${header_name}.hdr.${field_name} = mask->be64; \
//::      else:
        set_masked(value->data, mask->data, \
                   (uint8_t *) &match->flow.${header_name}.hdr.${field_name}, \
                   (uint8_t *) &match->wc.masks.${header_name}.hdr.${field_name}, \
                   sizeof match->flow.${header_name}.hdr.${field_name}); \
//::      #endif
        break; \
//::    #endfor
//::  #endfor
    \

#endif	/* OVS_MATCH_META_FLOW_H */