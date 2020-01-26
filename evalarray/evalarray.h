#ifndef EVALARRAY_H_
#define EVALARRAY_H_

#include <cstddef>

template<class T>
class evalarray final {
public:
    evalarray();
    evalarray(const evalarray<T>& other);
    evalarray(evalarray<T>&& other);

    ~evalarray();

private:
    std::size_t m_size;
    T* m_array;
};

template<class T>
evalarray<T>::evalarray()
    : m_size(0)
    , m_array(nullptr)
{}

template<class T>
evalarray<T>::~evalarray()
{
    delete[] m_array;
}

#endif // EVALARRAY_H_