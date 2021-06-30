#include "ppl/kernel/x86/common/expand/expand_common.h"

namespace ppl { namespace kernel { namespace x86 {

ppl::common::RetCode expand_ndarray_fp32(
    const ppl::nn::TensorShape *src_shape,
    const ppl::nn::TensorShape *dst_shape,
    const float *src,
    float *dst)
{
    return expand_ndarray_common<float>(src_shape, dst_shape, src, dst);
}

}}}; // namespace ppl::kernel::x86
