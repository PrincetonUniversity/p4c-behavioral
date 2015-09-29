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
 * File:   ovs_match_enum.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_ENUM_H
#define	OVS_MATCH_ENUM_H 1

/* -- Included in lib/meta-flow.h -- */

//::  import math
/* @Shahbaz:
 * 1. Make sure to add preceding tabs in the following fields. Otherwise, will result in errors.
 * 2. Prerequisites are not handled at this time.
 * 3. All fields are maskable at this time.
 */

//::  import math
//::
//::  ordered_field_instances_all__name_width = []
//::  ordered_header_instances_all_field__name_width = {}
//::  for header_name in ordered_header_instances_all:
//::    ordered_header_instances_all_field__name_width[header_name] = []
//::    proc_fields = []
//::    for field_name in header_info[header_name]["fields"]:
//::      if OVS_PARSER_IMP == 0:
//::        bit_width = field_info[field_name]["bit_width"]
//::        bit_width = int(math.ceil(bit_width/8.0)*8)
//::      elif OVS_PARSER_IMP == 1:
//::        bit_width = aligned_field_info[field_name]["bit_width"]
//::        field_name = aligned_field_info[field_name]["name"]
//::        if field_name in proc_fields:
//::          continue
//::        #endif
//::        proc_fields += [field_name]
//::      else:
//::        assert(False)
//::      #endif
//::      ordered_field_instances_all__name_width += [(field_name, bit_width)]
//::      ordered_header_instances_all_field__name_width[header_name] += [(field_name, bit_width)]
//::    #endfor
//::  #endfor
//::
//::  base_oxm_offset = 45
//::  for field_name, bit_width in ordered_field_instances_all__name_width:
    /* "${field_name}".
     *
     * ${field_name} field.
     *
     * Type: be${bit_width}.
     * Formatting: hexadecimal.
     * Maskable: bitwise.
     * Prerequisites: none.
     * Access: read/write.
     * NXM: none.
     * OXM: OXM_OF_${field_name.upper()}(${base_oxm_offset}) since OF1.5 and v2.3.
     */
    MFF_${field_name.upper()},
//::    base_oxm_offset += 1

//::  #endfor

/* Do NOT REMOVE THIS. */
    // MFF_N_IDS
#endif	/* OVS_MATCH_ENUM_H */