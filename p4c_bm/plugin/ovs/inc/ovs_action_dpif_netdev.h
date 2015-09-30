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
 * File:   ovs_action_dpif_netdev.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_DPIF_NETDEV_H
#define	OVS_ACTION_DPIF_NETDEV_H 1

/* -- Called in lib/dpif-netdev.c -- */
#define OVS_EXECUTE_CB \
//::  for action_name in action_info:
    case OVS_ACTION_ATTR__${action_name.upper()}: \
        OVS_NOT_REACHED(); \
//::  #endfor
    case OVS_ACTION_ATTR_DEPARSE: \
        OVS_NOT_REACHED(); \
    \

#endif	/* OVS_ACTION_DPIF_NETDEV_H */