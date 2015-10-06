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
 * File:   ovs_action_type.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_ACTION_TYPE_H
#define	OVS_ACTION_TYPE_H 1

//::  base_ofpat_offset = 31
//::  for header_name in ordered_header_instances_regular:
    /* OF1.5+(${base_ofpat_offset}): void. */
    OFPAT_RAW_ADD_HEADER_${header_name.upper()},
//::  base_ofpat_offset += 1

    /* OF1.5+(${base_ofpat_offset}): void. */
    OFPAT_RAW_RMV_HEADER_${header_name.upper()},
//::  base_ofpat_offset += 1

//::  #endfor

/* Do NOT REMOVE THIS. */
//}

#endif	/* OVS_ACTION_TYPE_H */