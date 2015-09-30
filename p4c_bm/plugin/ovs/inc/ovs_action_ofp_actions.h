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
//::  for action_name in action_info:
    OFPACT(_${action_name.upper()}, ofpact_null, ofpact, "${action_name}") \
//::  #endfor
    OFPACT(DEPARSE, ofpact_null, ofpact, "deparse") \
    \

/* -- Called in lib/ofp-actions.h -- */
#define OVS_OFPACT_STRUCTS \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_FUNCTIONS \
//::  for action_name in action_info:
    static enum ofperr \
    decode_OFPAT_RAW__${action_name.upper()}(struct ofpbuf *out) \
    { \
        ofpact_put__${action_name.upper()}(out); \
        return 0; \
    } \
    \
    static void \
    encode__${action_name.upper()}(const struct ofpact_null *null OVS_UNUSED, \
                   enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT__${action_name.upper()}(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse__${action_name.upper()}(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                  enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put__${action_name.upper()}(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format__${action_name.upper()}(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "${action_name}"); \
    } \
    \
//::  #endfor
    static enum ofperr \
    decode_OFPAT_RAW_DEPARSE(struct ofpbuf *out) \
    { \
        ofpact_put_DEPARSE(out); \
        return 0; \
    } \
    \
    static void \
    encode_DEPARSE(const struct ofpact_null *null OVS_UNUSED, \
                   enum ofp_version ofp_version, struct ofpbuf *out) \
    { \
        if (ofp_version >= OFP15_VERSION) { \
            put_OFPAT_DEPARSE(out); \
        } \
    } \
    \
    static char * OVS_WARN_UNUSED_RESULT \
    parse_DEPARSE(char *arg OVS_UNUSED, struct ofpbuf *ofpacts, \
                  enum ofputil_protocol *usable_protocols OVS_UNUSED) \
    { \
        ofpact_put_DEPARSE(ofpacts); \
        return NULL; \
    } \
    \
    static void \
    format_DEPARSE(const struct ofpact_null *a OVS_UNUSED, struct ds *s) \
    { \
        ds_put_cstr(s, "deparse"); \
    } \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_SET_OR_MOVE_ACTION \
//::  for action_name in action_info:
    case OFPACT__${action_name.upper()}: \
        return false; \
//::  #endfor
    case OFPACT_DEPARSE: \
        return false; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_IS_ALLOWED_IN_ACTIONS_SET \
//::  for action_name in action_info:
    case OFPACT__${action_name.upper()}: \
        return false; \
//::  #endfor
    case OFPACT_DEPARSE: \
        return false; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_INSTRUCTION_TYPE_FROM_OFPACT_TYPE \
//::  for action_name in action_info:
    case OFPACT__${action_name.upper()}: \
        return OVSINST_OFPIT11_APPLY_ACTIONS; \
//::  #endfor
    case OFPACT_DEPARSE: \
        return OVSINST_OFPIT11_APPLY_ACTIONS; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_CHECK__ \
//::  for action_name in action_info:
    case OFPACT__${action_name.upper()}: \
        return 0; \
//::  #endfor
    case OFPACT_DEPARSE: \
        return 0; \
    \

/* -- Called in lib/ofp-actions.c -- */
#define OVS_OUTPUTS_TO_PORT \
//::  for action_name in action_info:
    case OFPACT__${action_name.upper()}: \
        return false; \
//::  #endfor
    case OFPACT_DEPARSE: \
        return false; \
    \

#endif	/* OVS_ACTION_OFP_ACTIONS_H */