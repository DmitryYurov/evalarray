#ifndef EVALARRAY_H_
#define EVALARRAY_H_

#include <array>
#include <cstddef>
#include <numeric>
#include <utility>

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

    template<class U>
    evalarray(std::initializer_list<U> init);

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
    , m_data(new T[std::accumulate(std::begin(dims), std::end(dims), 1u,
                                   [](size_t lhs, size_t rhs) { return lhs * rhs; })] )
{
    static_assert (std::is_convertible<SizeType, size_t>::value,
        "Error in Eval::make_evalarray: dimensions must be convertible to size_t");

    for (size_t i = 0; i < NDim; ++i)
        m_dims[i] = dims[i];

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
    static_assert(sizeof... (indices) == NDim, "Error in evalarray::operator[]: number of indices"
                                               "does not match the array dimensions.");
    static_assert(std::is_convertible_v<std::common_type_t<Dims...>, int>,
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
        throw std::runtime_error("Error in evalarray::operator[]: indices exceed storage size.");

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
