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
 * File:   ovs_match_dp_packet.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_DP_PACKET_H
#define	OVS_MATCH_DP_PACKET_H 1

/* -- Called in lib/dp-packet.h -- */
#define OVS_HDR_ATTRS \
//::  for header_name in ordered_header_instances_regular:
    uint16_t ${header_name}_ofs; \
    struct ${header_name}_header ${header_name}; \
    uint8_t ${header_name}_valid; \
    \
//::  #endfor
    uint16_t payload_ofs; \
    \

/* -- Called in lib/dp-packet.h -- */
#define OVS_HDR_RESET_ATTRS \
//::  for header_name in ordered_header_instances_regular:
    b->${header_name}_ofs = UINT16_MAX; \
    memset(&b->${header_name}, 0x00, sizeof(struct ${header_name}_header)); \
    b->${header_name}_valid = 0; \
    \
//::  #endfor
    b->payload_ofs = UINT16_MAX; \
    \

#endif	/* OVS_MATCH_DP_PACKET_H */