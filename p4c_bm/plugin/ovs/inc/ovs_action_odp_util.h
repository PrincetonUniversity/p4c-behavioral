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
/* -- Called in lib/odp-util.c -- */
#define OVS_ACTION_LEN_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: return 0; \
    case OVS_ACTION_ATTR_REMOVE_HEADER_${header_name.upper()}: return 0; \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OVS_ACTION_ATTR_MODIFY_FIELD_${field_name.upper()}: \
        return sizeof(struct ovs_action_${field_name}); \
//::    #endfor
//::  #endfor
    \

/* -- Called in lib/odp-util.c -- */
#define OVS_FORMAT_ODP_ACTION_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_ACTION_ATTR_ADD_HEADER_${header_name.upper()}: \
        ds_put_cstr(ds, "add_header_${header_name}"); \
        break; \
    case OVS_ACTION_ATTR_REMOVE_HEADER_${header_name.upper()}: \
        ds_put_cstr(ds, "remove_header_${header_name}"); \
        break; \
//::    for field_name, bit_width in ordered_header_instances_all_field__name_width[header_name]:
    case OVS_ACTION_ATTR_MODIFY_FIELD_${field_name.upper()}: { \
        const struct ovs_action_${field_name} *oa = nl_attr_get(a); \
        ds_put_cstr(ds, "modify_field_${field_name}("); \
//::      if bit_width == 8 or bit_width == 16 or bit_width == 32 or bit_width == 64:
        ds_put_hex(ds, &oa->value, sizeof(oa->value)); \
        ds_put_char(ds, '/'); \
        ds_put_hex(ds, &oa->mask, sizeof(oa->mask)); \
//::      else:
//::        pass  #TODO: implement this for other bit_widths.
//::      #endif
        ds_put_char(ds, ')'); \
        break; \
    } \
//::    #endfor
//::  #endfor
    \

#endif	/* OVS_ACTION_ODP_UTIL_H */