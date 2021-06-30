#ifndef __ST_PPL_KERNEL_X86_FP32_REDUCE_SSE_REDUCE_KERNEL_FP32_SSE_H_
#define __ST_PPL_KERNEL_X86_FP32_REDUCE_SSE_REDUCE_KERNEL_FP32_SSE_H_

#include <string.h>
#include <float.h>
#include <nmmintrin.h>

#include "ppl/kernel/x86/common/internal_include.h"
#include "ppl/kernel/x86/common/reduce/reduce_common.h"

namespace ppl { namespace kernel { namespace x86 {

template <reduce_op_type_t _op>
inline float reduce_init_val_fp32(void)
{
    return 0;
}

template <>
inline float reduce_init_val_fp32<REDUCE_MAX>(void)
{
    return -__FLT_MAX__;
}

template <>
inline float reduce_init_val_fp32<REDUCE_MIN>(void)
{
    return __FLT_MAX__;
}

template <reduce_op_type_t _op>
static void reduce_preprocess_fp32_sse(
    float *dst,
    int64_t len)
{
    const float init_val    = reduce_init_val_fp32<_op>();
    const __m128 v_init_val = _mm_set1_ps(init_val);

    const int64_t simd_w      = 4;
    const int64_t unroll_len  = simd_w * 4;
    const int64_t unroll_body = round(len, unroll_len);

    PRAGMA_OMP_PARALLEL_FOR()
    for (int64_t i = 0; i < unroll_body; i += unroll_len) {
        _mm_storeu_ps(dst + i + simd_w * 0, v_init_val);
        _mm_storeu_ps(dst + i + simd_w * 1, v_init_val);
        _mm_storeu_ps(dst + i + simd_w * 2, v_init_val);
        _mm_storeu_ps(dst + i + simd_w * 3, v_init_val);
    }
    for (int64_t i = unroll_body; i < len; i++) {
        dst[i] = init_val;
    }
}

template <reduce_op_type_t _op>
inline float reduce_scalar_kernel_fp32(float a, float r);

template <>
inline float reduce_scalar_kernel_fp32<REDUCE_MEAN>(float a, float r)
{
    return a + r;
}

template <>
inline float reduce_scalar_kernel_fp32<REDUCE_MAX>(float a, float r)
{
    return a > r ? a : r;
}

template <>
inline float reduce_scalar_kernel_fp32<REDUCE_MIN>(float a, float r)
{
    return a < r ? a : r;
}

template <>
inline float reduce_scalar_kernel_fp32<REDUCE_SUM>(float a, float r)
{
    return a + r;
}

template <reduce_op_type_t _op>
inline __m128 reduce_vector_kernel_fp32_sse(__m128 a, __m128 r);

template <>
inline __m128 reduce_vector_kernel_fp32_sse<REDUCE_MEAN>(__m128 a, __m128 r)
{
    return _mm_add_ps(a, r);
}

template <>
inline __m128 reduce_vector_kernel_fp32_sse<REDUCE_MAX>(__m128 a, __m128 r)
{
    return _mm_max_ps(a, r);
}

template <>
inline __m128 reduce_vector_kernel_fp32_sse<REDUCE_MIN>(__m128 a, __m128 r)
{
    return _mm_min_ps(a, r);
}

template <>
inline __m128 reduce_vector_kernel_fp32_sse<REDUCE_SUM>(__m128 a, __m128 r)
{
    return _mm_add_ps(a, r);
}

template <reduce_op_type_t _op>
inline float reduce_vector_all_lanes_kernel_fp32_sse(__m128 v)
{
    float tmp[4];
    _mm_storeu_ps(tmp, v);
    tmp[0] = reduce_scalar_kernel_fp32<_op>(tmp[0], tmp[1]);
    tmp[2] = reduce_scalar_kernel_fp32<_op>(tmp[2], tmp[3]);
    tmp[0] = reduce_scalar_kernel_fp32<_op>(tmp[0], tmp[2]);
    return tmp[0];
}

template <reduce_op_type_t _op>
static void reduce_postprocess_fp32_sse(
    float *dst,
    int64_t len,
    float div)
{
    if (_op == REDUCE_MEAN) {
        const float rdiv    = 1.0f / div;
        const __m128 v_rdiv = _mm_set1_ps(rdiv);

        const int64_t simd_w      = 4;
        const int64_t unroll_len  = simd_w * 4;
        const int64_t unroll_body = round(len, unroll_len);

        PRAGMA_OMP_PARALLEL_FOR()
        for (int64_t i = 0; i < unroll_body; i += unroll_len) {
            __m128 v_dst_0 = _mm_loadu_ps(dst + i + simd_w * 0);
            __m128 v_dst_1 = _mm_loadu_ps(dst + i + simd_w * 1);
            __m128 v_dst_2 = _mm_loadu_ps(dst + i + simd_w * 2);
            __m128 v_dst_3 = _mm_loadu_ps(dst + i + simd_w * 3);

            v_dst_0 = _mm_mul_ps(v_dst_0, v_rdiv);
            v_dst_1 = _mm_mul_ps(v_dst_1, v_rdiv);
            v_dst_2 = _mm_mul_ps(v_dst_2, v_rdiv);
            v_dst_3 = _mm_mul_ps(v_dst_3, v_rdiv);

            _mm_storeu_ps(dst + i + simd_w * 0, v_dst_0);
            _mm_storeu_ps(dst + i + simd_w * 1, v_dst_1);
            _mm_storeu_ps(dst + i + simd_w * 2, v_dst_2);
            _mm_storeu_ps(dst + i + simd_w * 3, v_dst_3);
        }
        for (int64_t i = unroll_body; i < len; i++) {
            dst[i] *= rdiv;
        }
    }
}

}}}; // namespace ppl::kernel::x86

#endif // !__ST_PPL_KERNEL_X86_FP32_REDUCE_SSE_REDUCE_FP32_SSE_H_
