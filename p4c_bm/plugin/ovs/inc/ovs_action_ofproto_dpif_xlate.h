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
    case OFPACT_DEPARSE: \
        break; \
    \

/* -- Called in ofproto/ofproto-dpif-xlate.c -- */
#define OVS_COMPOSE_ACTIONS \
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
#define OVS_DO_XLATE_ACTIONS \
    case OFPACT_DEPARSE: \
        compose_deparse(ctx); \
        break; \
    \

#endif	/* OVS_ACTION_OFPROTO_DPIF_XLATE_H */