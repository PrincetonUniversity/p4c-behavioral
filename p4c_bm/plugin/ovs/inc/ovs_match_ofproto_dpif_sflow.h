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
 * File:   ovs_match_ofproto_dpif_sflow.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_OFPROTO_DPIF_SFLOW_H
#define	OVS_MATCH_OFPROTO_DPIF_SFLOW_H 1

/* -- Called in ofproto/ofproto-dpif-sflow.h -- */
#define OVS_SFLOW_READ_SET_ACTION_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: \
        break; \
//::  #endfor
    \

#endif	/* OVS_MATCH_OFPROTO_DPIF_SFLOW_H */