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
//::  for header_name in ordered_header_instances_regular:
    OFPACT(ADD_HEADER_${header_name.upper()}, ofpact_null, ofpact, "add_header_${header_name}") \
    OFPACT(RMV_HEADER_${header_name.upper()}, ofpact_null, ofpact, "rmv_header_${header_name}") \
//::  #endfor
    \

/* -- Called in lib/ofp-actions.h -- */
#define OVS_OFPACT_STRUCTS \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_STRUCTS \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_FUNCTIONS \
//::  for header_name in ordered_header_instances_regular:
    static enum ofperr \
    decode_OFPAT_RAW_ADD_HEADER_${header_name.upper()}(struct ofpbuf *out) \
    { \
        ofpact_put_ADD_HEADER_${header_name.upper()}(out); \
        return 0; \
    } \
    \
    static void \
    encode_ADD_HEADER_${header_name.upper()}(const struct ofpact_null *null OVS_UNUSED, \
                             enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT_ADD_HEADER_${header_name.upper()}(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_ADD_HEADER_${header_name.upper()}(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                            enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put_ADD_HEADER_${header_name.upper()}(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format_ADD_HEADER_${header_name.upper()}(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "add_header_${header_name}"); \
    } \
    \
    static enum ofperr \
    decode_OFPAT_RAW_RMV_HEADER_${header_name.upper()}(struct ofpbuf *out) \
    { \
        ofpact_put_RMV_HEADER_${header_name.upper()}(out); \
        return 0; \
    } \
    \
    static void \
    encode_RMV_HEADER_${header_name.upper()}(const struct ofpact_null *null OVS_UNUSED, \
                         enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT_RMV_HEADER_${header_name.upper()}(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_RMV_HEADER_${header_name.upper()}(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                        enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put_RMV_HEADER_${header_name.upper()}(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format_RMV_HEADER_${header_name.upper()}(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "rmv_header_${header_name}"); \
    } \
    \
//::  #endfor
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_SET_OR_MOVE_ACTION \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
        return false; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_ALLOWED_IN_ACTIONS_SET \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
        return false; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_INSTRUCTION_TYPE_FROM_OFPACT_TYPE \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
        return OVSINST_OFPIT11_APPLY_ACTIONS; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_CHECK__ \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
        return 0; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_OUTPUTS_TO_PORT \
//::  for header_name in ordered_header_instances_regular:
    case OFPACT_ADD_HEADER_${header_name.upper()}: \
    case OFPACT_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
        return false; \
    \

#endif	/* OVS_ACTION_OFP_ACTIONS_H */