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
 * File:   ovs_match_odp_util.h
 * Author: mshahbaz@cs.princeton.edu
 */

#ifndef OVS_MATCH_ODP_UTIL_H
#define	OVS_MATCH_ODP_UTIL_H 1

//::  import math
//::
//::  ordered_field_instances_non_virtual__name_width = []
//::  ordered_header_instances_non_virtual_field__name_width = {}
//::  for header_name in ordered_header_instances_non_virtual:
//::    ordered_header_instances_non_virtual_field__name_width[header_name] = []
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
//::      ordered_field_instances_non_virtual__name_width += [(field_name, bit_width)]
//::      ordered_header_instances_non_virtual_field__name_width[header_name] += [(field_name, bit_width)]
//::    #endfor
//::  #endfor
//::
/* -- Called in lib/odp-util.c -- */
#define OVS_KEY_ATTRS_TO_STRING_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: return "${header_name}"; \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case OVS_KEY_ATTR_${field_name.upper()}: return "${header_name}"; \
//::    #endfor
    case OVS_KEY_ATTR_${header_name.upper()}_VALID: return "${header_name}"; \
//::  #endfor
    \

/* -- Called in lib/odp-util.c -- */
#define OVS_FORMAT_ODP_KEY_ATTR_CASES \
//::  for header_name in ordered_header_instances_regular:
    case OVS_KEY_ATTR_${header_name.upper()}: { \
        const struct ovs_key_${header_name} *key = nl_attr_get(a); \
        const struct ovs_key_${header_name} *mask = ma ? nl_attr_get(ma) : NULL; \
        \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
//::      if bit_width == 8:
        format_u8x(ds, "${field_name}", key->${field_name}, MASK(mask, ${field_name}), verbose); \
//::      elif bit_width == 16:
        format_be16(ds, "${field_name}", key->${field_name}, MASK(mask, ${field_name}), verbose); \
//::      elif bit_width == 32:
        format_be32(ds, "${field_name}", key->${field_name}, MASK(mask, ${field_name}), verbose); \
//::      elif bit_width == 64:
        format_be64(ds, "${field_name}", key->${field_name}, MASK(mask, ${field_name}), verbose); \
//::      else:
        format_bex(ds, "${field_name}", (const uint8_t *) &key->${field_name}, \
                   mask ? (const uint8_t (*)[]) &mask->${field_name} : NULL, \
                   sizeof(struct ${field_name}_t), verbose); \
//::      #endif
//::    #endfor
        format_u8x(ds, "${header_name}_valid", key->${header_name}_valid, NULL, verbose); \
        ds_chomp(ds, ','); \
        break; \
    } \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    case OVS_KEY_ATTR_${field_name.upper()}: { \
//::      if bit_width == 8:
        const uint8_t *key = nl_attr_get(a); \
        format_u8x(ds, "${field_name}", *key, NULL, verbose); \
//::      elif bit_width == 16:
        const ovs_be16 *key = nl_attr_get(a); \
        format_be16(ds, "${field_name}", *key, NULL, verbose); \
//::      elif bit_width == 32:
        const ovs_be32 *key = nl_attr_get(a); \
        format_be32(ds, "${field_name}", *key, NULL, verbose); \
//::      elif bit_width == 64:
        const ovs_be64 *key = nl_attr_get(a); \
        format_be64(ds, "${field_name}", *key, NULL, verbose); \
//::      else:
        const struct ${field_name}_t *key = nl_attr_get(a); \
        format_bex(ds, "${field_name}", (const uint8_t *) key, NULL, \
                   sizeof(struct ${field_name}_t), verbose); \
//::      #endif
        ds_chomp(ds, ','); \
        break; \
    } \
//::    #endfor
    case OVS_KEY_ATTR_${header_name.upper()}_VALID: { \
        const uint8_t *key = nl_attr_get(a); \
        format_u8x(ds, "${header_name}_valid", *key, NULL, verbose); \
        ds_chomp(ds, ','); \
        break; \
    } \
//::  #endfor
    \

/* -- Called in lib/odp-util.c -- */
#define OVS_SET_FUNC_DECLS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    get_${header_name}_key(const struct flow *flow, struct ovs_key_${header_name} *${header_name}); \
    static void \
    put_${header_name}_key(const struct ovs_key_${header_name} *${header_name}, struct flow *flow); \
    \
//::  #endfor

/* -- Called in lib/odp-util.c -- */
#define OVS_SET_FUNC_DEFS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    get_${header_name}_key(const struct flow *flow, struct ovs_key_${header_name} *${header_name}) \
    { \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
        ${header_name}->${field_name} = flow->${header_name}.hdr.${field_name}; \
//::    #endfor
        ${header_name}->${header_name}_valid = flow->${header_name}.${header_name}_valid; \
    } \
    \
    static void \
    put_${header_name}_key(const struct ovs_key_${header_name} *${header_name}, struct flow *flow) \
    { \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
        flow->${header_name}.hdr.${field_name} = ${header_name}->${field_name}; \
//::    #endfor
        flow->${header_name}.${header_name}_valid = ${header_name}->${header_name}_valid; \
    } \
    \
//::  #endfor

/* -- Called in lib/odp-util.c -- */
#define OVS_COMMIT_ACTION_FUNCS \
//::  for header_name in ordered_header_instances_regular:
    static void \
    commit_set_${header_name}_action(const struct flow *flow, struct flow *base_flow, \
               struct ofpbuf *odp_actions, \
               struct flow_wildcards *wc, \
               bool use_masked) \
    { \
        struct ovs_key_${header_name} key, base, mask; \
        \
        get_${header_name}_key(flow, &key); \
        get_${header_name}_key(base_flow, &base); \
        get_${header_name}_key(&wc->masks, &mask); \
        \
        if (commit(OVS_KEY_ATTR_${header_name.upper()}, use_masked, \
                   &key, &base, &mask, sizeof key, odp_actions)) { \
            put_${header_name}_key(&base, base_flow); \
            put_${header_name}_key(&mask, &wc->masks); \
        } \
    } \
    \
//::  #endfor

/* -- Called in lib/odp-util.c -- */
#define OVS_COMMIT_ODP_ACTIONS_FUNCS \
//::  for header_name in ordered_header_instances_regular:
    commit_set_${header_name}_action(flow, base, odp_actions, wc, use_masked); \
//::  #endfor
    \

/* -- Called in lib/odp-util.c -- */
#define OVS_FLOW_KEY_ATTR_LENS \
//::  for header_name in ordered_header_instances_regular:
    [OVS_KEY_ATTR_${header_name.upper()}] = { .len = sizeof(struct ovs_key_${header_name}) }, \
//::    for field_name, bit_width in ordered_header_instances_non_virtual_field__name_width[header_name]:
    [OVS_KEY_ATTR_${field_name.upper()}] = { .len = ATTR_LEN_VARIABLE }, \
//::    #endfor
    [OVS_KEY_ATTR_${header_name.upper()}_VALID] = { .len = ATTR_LEN_VARIABLE }, \
//::  #endfor
    \

/* -- Called in lib/odp-util.c -- */
#define OVS_FLOW_KEY_FROM_FLOW \
//::  for header_name in ordered_header_instances_regular:
    struct ovs_key_${header_name} *${header_name}; \
    ${header_name} = nl_msg_put_unspec_uninit(buf, OVS_KEY_ATTR_${header_name.upper()}, sizeof *${header_name}); \
    get_${header_name}_key(data, ${header_name}); \
    \
//::  #endfor

/* -- Called in lib/odp-util.c -- */
#define OVS_FLOW_KEY_TO_FLOW \
//::  for header_name in ordered_header_instances_regular:
    if (present_attrs & (UINT64_C(1) << OVS_KEY_ATTR_${header_name.upper()})) { \
        const struct ovs_key_${header_name} *${header_name}; \
        \
        ${header_name} = nl_attr_get(attrs[OVS_KEY_ATTR_${header_name.upper()}]); \
        put_${header_name}_key(${header_name}, flow); \
        if (is_mask) { \
            expected_attrs |= UINT64_C(1) << OVS_KEY_ATTR_${header_name.upper()}; \
        } \
    } \
    if (!is_mask) { \
        expected_attrs |= UINT64_C(1) << OVS_KEY_ATTR_${header_name.upper()}; \
    } \
    \
//::  #endfor

#endif	/* OVS_MATCH_ODP_UTIL_H */