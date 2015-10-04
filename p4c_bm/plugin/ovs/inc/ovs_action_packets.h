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
 * File:   ovs_action_packets.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_PACKETS_H
#define	OVS_ACTION_PACKETS_H 1

/* -- Called in lib/packets.c -- */
#define OVS_FUNCTION_DECLS \
//::  for header_name in ordered_header_instances_regular:
    void add_header_${header_name}(struct dp_packet *packet); \
    void rmv_header_${header_name}(struct dp_packet *packet); \
//::  #endfor
    void deparse(struct dp_packet *packet); \
    \

/* -- Called in lib/packets.c -- */
#define OVS_FUNCTION_DEFS \
//::  for header_name in ordered_header_instances_regular:
    void add_header_${header_name}(struct dp_packet *packet) \
    { \
        packet->${header_name}_valid = true; \
    } \
    \
    void rmv_header_${header_name}(struct dp_packet *packet) \
    { \
        packet->${header_name}_valid = false; \
        packet->${header_name}_ofs = UINT16_MAX; \
    } \
    \
//::  #endfor
    void deparse(struct dp_packet *packet) \
    { \
        char *data = dp_packet_data(packet); \
        \
        /* get new payload offset */ \
        uint16_t new_payload_ofs = 0; \
//::  for header_name in ordered_header_instances_regular:
        if (packet->${header_name}_valid) { \
            new_payload_ofs += sizeof(struct ${header_name}_header); \
        } \
//::  #endfor
        \
        /* shift payload */ \
        if (packet->payload_ofs != new_payload_ofs) { \
            if (dp_packet_get_allocated(packet) >= (new_payload_ofs + (dp_packet_size(packet) - packet->payload_ofs))) { \
                memmove(data + new_payload_ofs, data + packet->payload_ofs, dp_packet_size(packet) - packet->payload_ofs); \
            } \
            else { /* error */ } \
            \
            dp_packet_set_size(packet, dp_packet_size(packet) + (new_payload_ofs - packet->payload_ofs)); \
            packet->payload_ofs = new_payload_ofs; \
        } \
        \
        /* write headers */ \
        uint16_t run_ofs = 0; \
//::  for header_name in ordered_header_instances_regular:
        if (packet->${header_name}_valid) { \
            memcpy(data + run_ofs, &packet->${header_name}, sizeof(struct ${header_name}_header)); \
            packet->${header_name}_ofs = run_ofs; \
            \
            run_ofs += sizeof(struct ${header_name}_header); \
        } \
//::  #endfor
    } \
    \

#endif	/* OVS_ACTION_PACKETS_H */