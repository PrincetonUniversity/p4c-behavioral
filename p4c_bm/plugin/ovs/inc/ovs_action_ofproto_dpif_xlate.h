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
/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_ACTION_HELPER_FUNCS \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_RECIRC_UNROLL_ACTIONS_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_REMOVE_HEADER_${header_name.upper()}: \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OFPACT_MODIFY_FIELD_${field_name.upper()}: \
//::    #endfor
//::  #endfor
        break; \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_AND_XLATE_FUNCS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    compose_add_header_${header_name}(struct xlate_ctx *ctx) \
    { \
        bool use_masked = ctx->xbridge->support.masked_set_action; \
        ctx->xout->slow |= commit_odp_actions(&ctx->xin->flow, &ctx->base_flow, \
                                          ctx->odp_actions, ctx->wc, \
                                          use_masked); \
        nl_msg_put_flag(ctx->odp_actions, OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}); \
    } \
    \
    static void \
    compose_remove_header_${header_name}(struct xlate_ctx *ctx) \
    { \
        bool use_masked = ctx->xbridge->support.masked_set_action; \
        ctx->xout->slow |= commit_odp_actions(&ctx->xin->flow, &ctx->base_flow, \
                                          ctx->odp_actions, ctx->wc, \
                                          use_masked); \
        nl_msg_put_flag(ctx->odp_actions, OVS_ACTION_ATTR_REMOVE_HEADER_${header_name.upper()}); \
    } \
    \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    static void \
    xlate_modify_field_${field_name}(struct xlate_ctx *ctx, \
                      const struct ofpact_modify_field_${field_name} *a) \
    { \
        bool use_masked = ctx->xbridge->support.masked_set_action; \
        struct flow *flow = &ctx->xin->flow; \
        struct flow *base_flow = &ctx->base_flow; \
        /* TODO: check if this is necessary. */ \
        ctx->xout->slow |= commit_odp_actions(flow, base_flow, \
                                              ctx->odp_actions, ctx->wc, \
                                              use_masked); \
        \
//::      if bit_width == 8 or bit_width == 16 or bit_width == 32 or bit_width == 64:
        apply_mask((const uint8_t *) &a->value, (const uint8_t *) &a->mask, \
               (uint8_t *) &flow->${header_name}.hdr.${field_name}, \
               sizeof(flow->${header_name}.hdr.${field_name})); \
        \
        if (flow->${header_name}.hdr.${field_name} != base_flow->${header_name}.hdr.${field_name}) \
        { \
            struct ovs_action_ethernet__etherType *oa; \
            oa = nl_msg_put_unspec_uninit(ctx->odp_actions, \
                                          OVS_ACTION_ATTR_MODIFY_FIELD_${field_name.upper()}, \
                                          sizeof *oa); \
            oa->value = flow->${header_name}.hdr.${field_name}; \
            oa->mask = a->mask; \
            base_flow->${header_name}.hdr.${field_name} = flow->${header_name}.hdr.${field_name}; \
        } \
//::      else:
//::        pass  #TODO: implement this for other bit_widths.
//::      #endif
    } \
    \
//::    #endfor
//::  #endfor

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_DO_XLATE_ACTIONS_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
        compose_add_header_${header_name}(ctx); \
        break; \
    case OFPACT_REMOVE_HEADER_${header_name.upper()}: \
        compose_remove_header_${header_name}(ctx); \
        break; \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OFPACT_MODIFY_FIELD_${field_name.upper()}: \
        xlate_modify_field_${field_name}(ctx, ofpact_get_MODIFY_FIELD_${field_name.upper()}(a)); \
        break; \
//::    #endfor
//::  #endfor
    \

#endif	/* OVS_ACTION_OFPROTO_DPIF_XLATE_H */