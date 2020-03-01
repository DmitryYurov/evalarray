#ifndef SLICE_H
#define SLICE_H

#include <functional>

namespace Eval {
template <class T, size_t NDim> class evalarray;

template<class T, size_t NDim>
class slice
{
public:
    slice(evalarray<T, NDim>& ref)
        : m_ref(ref)
    {}

private:
    std::reference_wrapper<evalarray<T, NDim>> m_ref;
};
}

#endif // SLICE_H
