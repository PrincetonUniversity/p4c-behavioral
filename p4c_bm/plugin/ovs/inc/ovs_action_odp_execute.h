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
 * File:   ovs_action_odp_execute.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_ODP_EXECUTE_H
#define	OVS_ACTION_ODP_EXECUTE_H 1

/* -- Called in lib/odp-execute.c -- */
#define OVS_ODP_EXECUTE_ACTIONS \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
        for (i = 0; i < cnt; i++) { \
            add_header_${header_name}(packets[i]); \
        } \
        break; \
    case OVS_ACTION_ATTR_RMV_HEADER_${header_name.upper()}: \
        for (i = 0; i < cnt; i++) { \
            rmv_header_${header_name}(packets[i]); \
        } \
        break; \
//::  #endfor
    case OVS_ACTION_ATTR_DEPARSE: \
        for (i = 0; i < cnt; i++) { \
            deparse(packets[i]); \
        } \
        break; \
    \

/* -- Called in lib/odp-execute.c -- */
#define OVS_REQUIRES_DATAPATH_ASSISTANCE \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
    case OVS_ACTION_ATTR_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
    case OVS_ACTION_ATTR_DEPARSE: \
        return false; \
    \

#endif	/* OVS_ACTION_ODP_EXECUTE_H */