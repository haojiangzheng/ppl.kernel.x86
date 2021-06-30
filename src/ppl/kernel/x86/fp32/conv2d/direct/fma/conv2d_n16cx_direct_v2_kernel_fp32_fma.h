#ifndef __ST_PPL_KERNEL_X86_FP32_CONV2D_DIRECT_FMA_CONV2D_N16CX_DIRECT_V2_KERNEL_FP32_FMA_H_
#define __ST_PPL_KERNEL_X86_FP32_CONV2D_DIRECT_FMA_CONV2D_N16CX_DIRECT_V2_KERNEL_FP32_FMA_H_

#include "ppl/kernel/x86/common/internal_include.h"
#include "ppl/kernel/x86/fp32/conv2d.h"

#define KERNEL_FLAG_LD_BIAS() (1 << 0)
#define KERNEL_FLAG_AD_BIAS() (1 << 1)
#define KERNEL_FLAG_RELU()    (1 << 2)
#define KERNEL_FLAG_RELU6()   (1 << 3)

#define PICK_PARAM(T, PARAM, IDX) *(T*)(PARAM + IDX)

#define PRIV_PARAM_LEN() 10
#define SRC_IDX()        0
#define HIS_IDX()        1
#define DST_IDX()        2
#define FLT_IDX()        3
#define BIAS_IDX()       4
#define OW_IDX()         5
#define KH_START_IDX()   6
#define KH_END_IDX()     7
#define KW_START_IDX()   8
#define KW_END_IDX()     9

#define SHAR_PARAM_LEN()     8
#define CHANNELS_IDX()       0
#define SRC_ICB_STRIDE_IDX() 1
#define SRC_SW_STRIDE_IDX()  2
#define SRC_DH_STRIDE_IDX()  3
#define SRC_DW_STRIDE_IDX()  4
#define FLAGS_IDX()          5
#define KH_IDX()             6
#define KW_IDX()             7

#define CH_DT_BLK() 16
#define CH_RF_BLK() 8

#define NT_STORE_OPT() 2
#define STRIDE_W_OPT() 3

#define MAX_OC_RF() 2
#define MAX_OW_RF() 6

#define BLK1X6_OC_RF() 2
#define BLK1X6_OW_RF() 6

namespace ppl { namespace kernel { namespace x86 {

typedef void (*conv2d_n16cx_direct_v2_kernel_fp32_fma_func_t)(const int64_t*, const int64_t*);

extern conv2d_n16cx_direct_v2_kernel_fp32_fma_func_t
    conv2d_n16cx_direct_v2_kernel_fp32_fma_pad_table[NT_STORE_OPT()][MAX_OC_RF()];
extern conv2d_n16cx_direct_v2_kernel_fp32_fma_func_t
    conv2d_n16cx_direct_v2_kernel_fp32_fma_blk_table[NT_STORE_OPT()][STRIDE_W_OPT()][MAX_OC_RF()][MAX_OW_RF()];

}}}; // namespace ppl::kernel::x86

#endif
