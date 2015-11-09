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
 * File:   ovs_action_ofp_actions.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_OFP_ACTIONS_H
#define	OVS_ACTION_OFP_ACTIONS_H 1

/* -- Called in lib/ofp-actions.h -- */
#define OVS_OFPACTS \
    \

/* -- Called in lib/ofp-actions.h -- */
#define OVS_OFPACT_STRUCTS \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_OFP_ACTION_STRUCTS \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_OFP_FUNCS \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_SET_OR_MOVE_ACTION_CASES \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_ALLOWED_IN_ACTIONS_SET_CASES \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_INSTRUCTION_TYPE_FROM_OFPACT_TYPE_CASES \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_CHECK___CASES \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_OUTPUTS_TO_PORT_CASES \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_ENCODE_ADD_HEADER_CHECKS \
//::  for header_name in ordered_header_instances_regular:
    if (!memcmp("${header_name}", ah->name, ah->n_bytes)) { \
        ofpact_put_set_field(out, ofp_version, MFF_${header_name.upper()}_VALID, 1); \
        return; \
    } \
    \
//::  #endfor

/* -- Called in lib/ofp-actions.c -- */
#define OVS_ENCODE_REMOVE_HEADER_CHECKS \
//::  for header_name in ordered_header_instances_regular:
    if (!memcmp("${header_name}", rh->name, rh->n_bytes)) { \
        ofpact_put_set_field(out, ofp_version, MFF_${header_name.upper()}_VALID, 0); \
        return; \
    } \
    \
//::  #endfor

#endif	/* OVS_ACTION_OFP_ACTIONS_H */