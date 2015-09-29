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
 * File:   ovs_match_match.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_MATCH_H
#define	OVS_MATCH_MATCH_H 1

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
/* -- Called in lib/match.c -- */
#define OVS_MATCH_FORMAT \
//::  for header_name in ordered_header_instances_all:
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
//::      if bit_width == 8:
    format_be8_masked(s, "${field_name}", f->${header_name}.hdr.${field_name}, \
                      wc->masks.${header_name}.hdr.${field_name}); \
//::      elif bit_width == 16:
    format_be16_masked(s, "${field_name}", f->${header_name}.hdr.${field_name}, \
                       wc->masks.${header_name}.hdr.${field_name}); \
//::      elif bit_width == 32:
    format_be32_masked(s, "${field_name}", f->${header_name}.hdr.${field_name}, \
                       wc->masks.${header_name}.hdr.${field_name}); \
//::      elif bit_width == 64:
    format_be64_masked(s, "${field_name}", f->${header_name}.hdr.${field_name}, \
                       wc->masks.${header_name}.hdr.${field_name}); \
//::      else:
    format_masked(s, "${field_name}", \
                  f->${header_name}.hdr.${field_name}, \
                  wc->masks.${header_name}.hdr.${field_name}, \
                  sizeof(f->${header_name}.hdr.${field_name})); \
//::      #endif
//::    #endfor
//::  #endfor
    \

#endif	/* OVS_MATCH_MATCH_H */