// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

#include "ppl/kernel/x86/fp32/conv2d/avx512/conv2d_n16cx_depthwise_blk1x1_kernel_fp32_avx512.h"
#include "ppl/kernel/x86/fp32/conv2d/avx512/conv2d_n16cx_depthwise_blk1x31_kernel_fp32_avx512.h"

namespace ppl { namespace kernel { namespace x86 {

conv2d_n16cx_depthwise_kernel_fp32_avx512_func_t
conv2d_n16cx_depthwise_kernel_fp32_avx512_pad_table[NT_STORE_OPT()] =
{
    conv2d_n16cx_depthwise_fp32_avx512_blk1x1_kernel<false>,
    conv2d_n16cx_depthwise_fp32_avx512_blk1x1_kernel<true>,
};

#define DEPTHWISE_BLK_KERNEL_TABLE_BLK(NT_STORE, STRIDE_W) \
    {\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 1>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 2>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 3>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 4>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 5>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 6>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 7>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 8>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 9>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 10>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 11>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 12>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 13>,\
        conv2d_n16cx_depthwise_fp32_avx512_blk1x31_kernel<NT_STORE, STRIDE_W, 14>,\
    }

conv2d_n16cx_depthwise_kernel_fp32_avx512_func_t
conv2d_n16cx_depthwise_kernel_fp32_avx512_blk_table[NT_STORE_OPT()][STRIDE_W_OPT()][MAX_OW_RF()] =
{
    {
        DEPTHWISE_BLK_KERNEL_TABLE_BLK(false, 0),
        DEPTHWISE_BLK_KERNEL_TABLE_BLK(false, 1),
        DEPTHWISE_BLK_KERNEL_TABLE_BLK(false, 2),
    },
    {
        DEPTHWISE_BLK_KERNEL_TABLE_BLK(true, 0),
        DEPTHWISE_BLK_KERNEL_TABLE_BLK(true, 1),
        DEPTHWISE_BLK_KERNEL_TABLE_BLK(true, 2),
    },
};

}}};
