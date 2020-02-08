#ifndef EVALARRAY_H_
#define EVALARRAY_H_

#include <cstddef>

template<class T>
class evalarray {
public:
    // constructors
    evalarray();
    evalarray(const evalarray<T>& other);
    evalarray(evalarray<T>&& other);
    evalarray(const T* plain_array, size_t count);

    virtual ~evalarray();

    // operators
    T& operator[](size_t index) { return m_array[index]; }
    const T& operator[](size_t index) const { return m_array[index]; }

    std::size_t size() const { return m_size; }

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
evalarray<T>::evalarray(const T* plain_array, size_t count)
    : m_array(new T[count])
    , m_size(count)
{
    for (size_t i = 0; i < m_size; ++i)
        m_array[i] = plain_array[i];
}

template<class T>
evalarray<T>::~evalarray()
{
    delete[] m_array;
}

#endif // EVALARRAY_H_
