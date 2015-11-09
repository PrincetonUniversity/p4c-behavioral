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

/* -- Called in lib/packets.h -- */
#define OVS_FUNC_DECLS \
    \

/* -- Called in lib/packets.c -- */
#define OVS_FUNC_DEFS \
    \

/* -- Called in lib/packets.c -- */
#define OVS_ADD_HEADER_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR__${header_name.upper()}: \
        packet->_${header_name}_valid = true; \
        break; \
    \
//::  #endfor

/* -- Called in lib/packets.c -- */
#define OVS_REMOVE_HEADER_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR__${header_name.upper()}: \
        packet->_${header_name}_valid = false; \
        packet->_${header_name}_ofs = UINT16_MAX; \
        break; \
    \
//::  #endfor

/* -- Called in lib/packets.c -- */
#define OVS_DEPARSE_NEW_PAYLOAD_OFS \
//::  for header_name in ordered_header_instances_regular:
    if (packet->_${header_name}_valid) { \
        new_payload_ofs += sizeof(struct _${header_name}_header); \
    } \
//::  #endfor
    \

/* -- Called in lib/packets.c -- */
#define OVS_DEPARSE_WRITE_HEADERS \
//::  for header_name in ordered_header_instances_regular:
    if (packet->_${header_name}_valid) { \
        memcpy(data + run_ofs, &packet->_${header_name}, sizeof(struct _${header_name}_header)); \
        packet->_${header_name}_ofs = run_ofs; \
        \
        run_ofs += sizeof(struct _${header_name}_header); \
    } \
//::  #endfor
    \

#endif	/* OVS_ACTION_PACKETS_H */