#ifndef EVALARRAY_H_
#define EVALARRAY_H_

#include <numeric>
#include <utility>

#include "evalarray_utils.h"

namespace Eval
{
template<class T, size_t NDim = 1>
class evalarray {
public:

    using value_type = T;

    static_assert (std::is_copy_constructible<std::decay_t<T>>::value,
            "Error in evalarray<T>: value type must be copy constructible");

    // constructors

    //! Constructs a zero-size evalarray
    evalarray();

    evalarray(const evalarray<T, NDim>& other);
    evalarray(evalarray<T, NDim>&& other);

    // Constructs an evalarray with dimensions specified by _dims_.
    // Values are initialized with copies of _val_.
    template<class SizeType>
    evalarray(SizeType const (&dims)[NDim], const T& val);

    virtual ~evalarray();

    // access operators
    template<class... Dims>
    T& operator()(Dims... indices);

    template<class... Dims>
    const T& operator()(Dims... indices) const;

    // direct data access
    const T* data() const { return m_data; }

    // size and dimensions
    std::size_t size() const;
    constexpr size_t n_dimensions() const { return NDim; }
    std::array<size_t, NDim> dimensions() const { return m_dims; }

private:
    std::array<std::size_t, NDim> m_dims;
    T* m_data;
};

template<class T, class SizeType, size_t NDim>
evalarray(SizeType const (&)[NDim], const T&) -> evalarray<T, NDim>;

template<class T, size_t NDim>
evalarray<T, NDim>::evalarray()
    : m_dims{}
    , m_data(nullptr)
{}

template<class T, size_t NDim>
template<class SizeType>
evalarray<T, NDim>::evalarray(SizeType const (&dims)[NDim], const T& val)
    : m_dims{}
    , m_data(nullptr)
{
    static_assert (std::is_integral_v<SizeType>,
        "Error during evalarray construction: dimensions must be convertible to an integral type");

    for (size_t i = 0; i < NDim; ++i) {
        if (dims[i] < 0)
            throw std::runtime_error("Error during evalarray construction:"
                                     "negative dimension size encountered");
        m_dims[i] = dims[i];
    }

    m_data = new T[size()];
    for (size_t i = 0, tot_size = size(); i < tot_size; ++i)
        m_data[i] = val;
}

template<class T, size_t NDim>
evalarray<T, NDim>::~evalarray()
{
    delete[] m_data;
    m_data = nullptr;
}

template<class T, size_t NDim>
template<class... Dims>
T& evalarray<T, NDim>::operator()(Dims... indices)
{
    auto& result = const_cast<const evalarray<T, NDim>*>(this)->operator()(std::forward<Dims>(indices)...);
    return const_cast<T&>(result);
}

template<class T, size_t NDim>
template<class... Dims>
const T& evalarray<T, NDim>::operator()(Dims... indices) const
{
    static_assert(sizeof... (indices) == NDim, "Error in evalarray::operator[]: number of indices "
                                               "does not match the array dimensions.");
    static_assert(std::is_integral_v<std::common_type_t<Dims...>>,
            "Error in evalarray::operator[]: indices must be convertible to integral values");

    static const auto is_negative = [](auto param) {return param < 0;};
    for (bool statement : {is_negative(indices)...})
        if (statement)
            throw std::runtime_error("Error in evalarray::operator[]: negative indices encountered");

    std::array point = {static_cast<size_t>(indices)...};
    size_t total_position = 0;
    for (size_t i = 0; i < NDim; ++i) {
        const size_t step = std::accumulate(m_dims.begin() + i + 1, m_dims.end(), 1,
                                            [](size_t lhs, size_t rhs) {return lhs * rhs;});
        total_position += point[i] * step;
    }

    if (total_position >= size())
        throw std::runtime_error("Error in evalarray::operator[]: indices exceed the storage size.");

    return m_data[total_position];
}

template<class T, size_t NDim>
std::size_t evalarray<T, NDim>::size() const
{
    size_t size = 1;
    for (size_t val: m_dims)
        size *= val;

    return size;
}

} // namespace eval
#endif // EVALARRAY_H_
