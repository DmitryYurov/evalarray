#include "evalarray.h"
#include "ITest.h"

namespace {
template <class T>
bool createEmptyArray();

template <class T>
bool createFromPlainArray();
}

ADD_TEST(CreateEmpty) {
    if (!createEmptyArray<double>())
        return false;

    if (!createEmptyArray<int>())
        return false;

    return true;
}

ADD_TEST(CreateFromPlainArray)
{
    if (!createFromPlainArray<double>())
        return false;

    if (!createFromPlainArray<int>())
        return false;

    return true;
}

namespace {
template <class T>
bool createEmptyArray()
{
    evalarray<T> var;
    if (var.size() != 0)
        return false;

    return true;
}

template <class T>
bool createFromPlainArray()
{
    T* array = new T[10];
    for (size_t i = 0; i < 10; ++i)
        array[i] = T();

    evalarray<T> val(array, 10);
    if (val.size() != 10)
        return false;

    for (size_t i = 0; i < 10; ++i)
        if (val[i] != T())
            return false;

    delete[] array;
    array = nullptr;

    for (size_t i = 0; i < 10; ++i)
        if (val[i] != T())
            return false;

    return true;
}
}
