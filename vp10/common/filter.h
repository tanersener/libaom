/*
 *  Copyright (c) 2011 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VP10_COMMON_FILTER_H_
#define VP10_COMMON_FILTER_H_

#include "./vpx_config.h"
#include "vpx/vpx_integer.h"
#include "vpx_dsp/vpx_filter.h"
#include "vpx_ports/mem.h"


#ifdef __cplusplus
extern "C" {
#endif

#define EIGHTTAP            0
#define EIGHTTAP_SMOOTH     1
#define EIGHTTAP_SHARP      2

#if CONFIG_EXT_INTERP
#define SUPPORT_NONINTERPOLATING_FILTERS 0  /* turn it on for experimentation */
#define SWITCHABLE_FILTERS  5 /* Number of switchable filters */

#if SWITCHABLE_FILTERS == 4

#define EIGHTTAP_SMOOTH2    3

#elif SWITCHABLE_FILTERS == 5

#define EIGHTTAP_SMOOTH2    3
#define EIGHTTAP_SHARP2     4

#endif  // SWITCHABLE_FILTERS

#else
#define SWITCHABLE_FILTERS  3 /* Number of switchable filters */
#endif  // CONFIG_EXT_INTERP

// TODO(jingning): Align the experiment flags and clean this up.
#define FILTER_12TAP (!CONFIG_EXT_INTERP)
#if FILTER_12TAP
#define SHARP_FILTER_12TAP (SWITCHABLE_FILTERS + 1)
#endif

// The codec can operate in four possible inter prediction filter mode:
// 8-tap, 8-tap-smooth, 8-tap-sharp, and switching between the three.

#define BILINEAR            (SWITCHABLE_FILTERS)
#define SWITCHABLE          (SWITCHABLE_FILTERS + 1)  /* the last one */
#define SWITCHABLE_FILTER_CONTEXTS (SWITCHABLE_FILTERS + 1)

typedef uint8_t INTERP_FILTER;

extern const InterpKernel *vp10_filter_kernels[SWITCHABLE_FILTERS + 1];

#if CONFIG_EXT_INTRA
typedef enum {
  INTRA_FILTER_LINEAR,
  INTRA_FILTER_8TAP,
  INTRA_FILTER_8TAP_SHARP,
  INTRA_FILTER_8TAP_SMOOTH,
  INTRA_FILTERS,
} INTRA_FILTER;

extern const InterpKernel *vp10_intra_filter_kernels[INTRA_FILTERS];
#endif  // CONFIG_EXT_INTRA

typedef struct InterpFilterParams {
  const int16_t* filter_ptr;
  uint16_t tap;
  uint16_t subpel_shifts;
} InterpFilterParams;

InterpFilterParams vp10_get_interp_filter_params(
    const INTERP_FILTER interp_filter);
static INLINE const int16_t* vp10_get_interp_filter_kernel(
    const InterpFilterParams filter_params, const int subpel) {
  return filter_params.filter_ptr + filter_params.tap * subpel;
}
#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // VP10_COMMON_FILTER_H_
