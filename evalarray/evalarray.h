#ifndef EVALARRAY_H_
#define EVALARRAY_H_

#include <array>
#include <cstddef>
#include <numeric>
#include <utility>

namespace Eval
{

//! Constructs an evalarray with dimensions specified by the arguments.
//! Values are default initialized.
template<class T, class... Dims>
auto make_evalarray(Dims... dims);

template<class T, size_t NDim = 1>
class evalarray {
public:
    static_assert (std::is_copy_constructible<std::decay_t<T>>::value,
            "Error in evalarray<T>: value type must be copy constructible");

    // constructors

    //! Constructs an evalarray with one dimension of zero size
    evalarray();

    template<class U>
    evalarray(std::initializer_list<U> init);

    evalarray(const evalarray<T, NDim>& other);
    evalarray(evalarray<T, NDim>&& other);

    //! Constructs an evalarray with dimensions specified by _dims_.
    //! Values are initialized with copies of _val_.
    template<class SizeType>
    evalarray(const T& val, SizeType const (&dims)[NDim]);

    virtual ~evalarray();

    // operators
    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }

    // methods
    std::size_t size() const;
    std::size_t nDims() const { return m_dims.size(); }

private:
    std::array<std::size_t, NDim> m_dims;
    T* m_data;
};

template<class T, class SizeType, size_t NDim>
    evalarray(const T&, SizeType const (&)[NDim]) -> evalarray<T, NDim>;

template<class T, class... Dims>
auto make_evalarray(Dims... dims)
{
    static_assert (std::is_default_constructible<std::decay_t<T>>::value,
            "Error in Eval::make_evalarray: value type must be default constructible");
    static_assert ((std::is_convertible<Dims, size_t>::value && ...),
            "Error in Eval::make_evalarray: dimensions must be convertible to size_t");

    constexpr size_t n_dims = sizeof... (dims);
    if constexpr (n_dims > 0)
        return evalarray<T, n_dims>(T(), { std::forward<Dims>(dims)... });
    else
        return evalarray<T, 1>();
}

template<class T, size_t NDim>
evalarray<T, NDim>::evalarray()
    : m_dims{}
    , m_data(nullptr)
{}

template<class T, size_t NDim>
template<class SizeType>
evalarray<T, NDim>::evalarray(const T& val, SizeType const (&dims)[NDim])
    : m_dims{}
    , m_data(nullptr)
    //, m_data(new T[std::accumulate(dims.begin(), dims.end(), 1u,
    //                               [](size_t lhs, size_t rhs) { return lhs * rhs; })] )
{
    static_assert (std::is_convertible<SizeType, size_t>::value,
        "Error in Eval::make_evalarray: dimensions must be convertible to size_t");

    for (size_t i = 0; i < NDim; ++i)
        m_dims[i] = dims[i];

    //for (size_t i = 0, tot_size = size(); i < tot_size; ++i)
    //    m_data[i] = val;
}

template<class T, size_t NDim>
evalarray<T, NDim>::~evalarray()
{
    delete[] m_data;
    m_data = nullptr;
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
