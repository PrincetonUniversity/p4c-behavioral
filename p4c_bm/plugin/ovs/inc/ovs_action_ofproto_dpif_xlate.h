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

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_ACTION_HELPERS \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_RECIRC_UNROLL_ACTIONS \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
    case OFPACT_DEPARSE: \
        break; \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_ACTIONS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    compose_add_header_${header_name}(struct xlate_ctx *ctx) \
    { \
        bool use_masked = ctx->xbridge->support.masked_set_action; \
        ctx->xout->slow |= commit_odp_actions(&ctx->xin->flow, &ctx->base_flow, \
                                          ctx->xout->odp_actions, \
                                          &ctx->xout->wc, use_masked); \
        nl_msg_put_flag(ctx->xout->odp_actions, OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}); \
    } \
    \
    static void \
    compose_rmv_header_${header_name}(struct xlate_ctx *ctx) \
    { \
        bool use_masked = ctx->xbridge->support.masked_set_action; \
        ctx->xout->slow |= commit_odp_actions(&ctx->xin->flow, &ctx->base_flow, \
                                          ctx->xout->odp_actions, \
                                          &ctx->xout->wc, use_masked); \
        nl_msg_put_flag(ctx->xout->odp_actions, OVS_ACTION_ATTR_RMV_HEADER_${header_name.upper()}); \
    } \
    \
//::  #endfor
    static void \
    compose_deparse(struct xlate_ctx *ctx) \
    { \
        bool use_masked = ctx->xbridge->support.masked_set_action; \
        ctx->xout->slow |= commit_odp_actions(&ctx->xin->flow, &ctx->base_flow, \
                                          ctx->xout->odp_actions, \
                                          &ctx->xout->wc, use_masked); \
        nl_msg_put_flag(ctx->xout->odp_actions, OVS_ACTION_ATTR_DEPARSE); \
    } \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_DO_XLATE_ACTIONS_VARS \
    const struct ofpact_add_to_field *add_to_field; \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_DO_XLATE_ACTIONS \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
        compose_add_header_${header_name}(ctx); \
        break; \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
        compose_rmv_header_${header_name}(ctx); \
        break; \
//::  #endfor
    case OFPACT_ADD_TO_FIELD: \
        add_to_field = ofpact_get_ADD_TO_FIELD(a); \
        mf = add_to_field->field; \
        \
        /* A flow may wildcard nw_frag.  Do nothing if setting a trasport */ \
        /* header field on a packet that does not have them. */ \
        mf_mask_field_and_prereqs(mf, &wc->masks); \
        if (mf_are_prereqs_ok(mf, flow)) { \
            mf_add_to_flow_value(mf, &add_to_field->value, flow); \
        } \
        break; \
    case OFPACT_DEPARSE: \
        compose_deparse(ctx); \
        break; \
    \

#endif	/* OVS_ACTION_OFPROTO_DPIF_XLATE_H */