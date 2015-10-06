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
 * File:   ovs_action_odp_util.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_ODP_UTIL_H
#define	OVS_ACTION_ODP_UTIL_H 1

/* -- Called in lib/odp-util.c -- */
#define OVS_ACTION_LEN \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
    case OVS_ACTION_ATTR_RMV_HEADER_${header_name.upper()}: \
//::  #endfor
        return 0; \
    \

/* -- Called in lib/odp-util.c -- */
#define OVS_FORMAT_ACTION \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
        ds_put_cstr(ds, "add_header_${header_name}"); \
        break; \
    case OVS_ACTION_ATTR_RMV_HEADER_${header_name.upper()}: \
        ds_put_cstr(ds, "rmv_header_${header_name}"); \
        break; \
//::  #endfor
    \

#endif	/* OVS_ACTION_ODP_UTIL_H */