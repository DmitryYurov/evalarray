#ifndef EVALARRAYUTILS_H
#define EVALARRAYUTILS_H

#include <array>
#include <cstddef>

namespace Eval {
template <class SizeType, size_t NDim>
std::array<size_t, NDim> makeArray(SizeType const (&dims)[NDim])
{
    static_assert (std::is_integral_v<SizeType>,
        "Error during dimension array construction: dimensions must be convertible to an integral type");

    std::array<size_t, NDim> result;

    for (size_t i = 0; i < NDim; ++i) {
        if (dims[i] < 0)
            throw std::runtime_error("Error during dimension array construction:"
                                     "negative dimension size encountered");
        result[i] = dims[i];
    }

    return result;
}
}

#endif // EVALARRAYUTILS_H
