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
 * File:   ovs_action_ofproto_dpif_xlate.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_OFPROTO_DPIF_XLATE_H
#define	OVS_ACTION_OFPROTO_DPIF_XLATE_H 1

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
/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_ACTION_HELPER_FUNCS \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_RECIRC_UNROLL_ACTIONS_CASES \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_AND_XLATE_FUNCS \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_DO_XLATE_ACTIONS_CASES \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_CALC_FIELDS_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case MFF_${field_name.upper()}: \
        nl_msg_put_flag(ctx->odp_actions, OVS_CALC_FIELD_ATTR_${field_name.upper()}); \
        break; \
//::    #endfor
//::  #endfor
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_ADD_TO_FIELD_CASES \
//::  for header_name in ordered_header_instances_regular:
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//    case MFF_${field_name.upper()}: \
//::      if bit_width == 8:
//			memset(&wc->masks.${header_name}.hdr.${field_name}, 0xff, sizeof value->u8); \
//			union mf_value tmp; \
//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
//				(uint8_t *) &tmp, sizeof value->u8); \
//			union mf_value added_value = flow->${header_name}.hdr.${field_name} + tmp \;
//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
//			(uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->u8); \
//::      elif bit_width == 16:
//			memset(&wc->masks.${header_name}.hdr.${field_name}, 0xff, sizeof value->be16); \
//			union mf_value tmp; \
//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
//				(uint8_t *) &tmp, sizeof value->be16); \
//			union mf_value added_value = htons(
//				ntohs(flow->${header_name}.hdr.${field_name}) + ntohs(tmp)) \;
//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->be16); \
//			break;
//::      elif bit_width == 32:
//          union mf_value tmp; \
//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
//              (uint8_t *) &tmp, sizeof value->be32); \
//			union mf_value added_value = htonl(
//				ntohl(flow->${header_name}.hdr.${field_name}) + ntohl(tmp)) \;
//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->be32); \
//			break;
//::      elif bit_width == 64:
//          union mf_value tmp; \
//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
//              (uint8_t *) &tmp, sizeof value->be64); \
//			union mf_value added_value = htonll(
//				ntohll(flow->${header_name}.hdr.${field_name}) + ntohll(tmp)) \;
//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->be64); \
//::      else:
//::        pass  # TODO: handle this case (i.e., for arbitrary byte sizes).
//::      #endif
//        break; \
//::    #endfor
//::  #endfor
//    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_SUB_FROM_FIELD_CASES \
	//::  for header_name in ordered_header_instances_regular:
	//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
	//    case MFF_${field_name.upper()}: \
	//::      if bit_width == 8:
	//			memset(&wc->masks.${header_name}.hdr.${field_name}, 0xff, sizeof value->u8); \
	//          union mf_value tmp; \
	//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
	//              (uint8_t *) &tmp, sizeof value->u8); \
	//			union mf_value added_value = flow->${header_name}.hdr.${field_name} - tmp \;
	//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
	//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->u8); \
	//			break;
	//::      elif bit_width == 16:
	//			memset(&wc->masks.${header_name}.hdr.${field_name}, 0xff, sizeof value->be16); \
	//          union mf_value tmp; \
	//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
	//              (uint8_t *) &tmp, sizeof value->be16); \
	//			union mf_value added_value = htons(
	//				ntohs(flow->${header_name}.hdr.${field_name}) - ntohs(tmp)) \;
	//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
	//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->be16); \
	//			break;
	//::      elif bit_width == 32:
	//          union mf_value tmp; \
	//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
	//              (uint8_t *) &tmp, sizeof value->be32); \
	//			union mf_value added_value = htonl(
	//				ntohl(flow->${header_name}.hdr.${field_name}) - ntohl(tmp)) \;
	//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
	//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->be32); \
	//			break;
	//::      elif bit_width == 64:
	//          union mf_value tmp; \
	//			apply_mask((const uint8_t *) value, (const uint8_t *) mask, \
	//              (uint8_t *) &tmp, sizeof value->be64); \
	//			union mf_value added_value = htonll(
	//				ntohll(flow->${header_name}.hdr.${field_name}) - ntohll(tmp)) \;
	//			apply_mask((const uint8_t *) added_value, (const uint8_t *) mask, \
	//              (uint8_t *) &flow->${header_name}.hdr.${field_name}, sizeof value->be64); \
	//::      else:
	//::        pass  # TODO: handle this case (i.e., for arbitrary byte sizes).
	//::      #endif
	//        break; \
	//::    #endfor
	//::  #endfor
	//    \

#endif	/* OVS_ACTION_OFPROTO_DPIF_XLATE_H */
