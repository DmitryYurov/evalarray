#include "evalarray.h"
#include "ITest.h"

using namespace Eval;

ADD_TEST(DefaultConstructor) {
    evalarray<double> var;
    if (var.size() != 0)
        return false;
    if (var.n_dimensions() != 1)
        return false;

    evalarray<int> var2;
    if (var2.size() != 0)
        return false;
    if (var2.n_dimensions() != 1)
        return false;

    evalarray<double, 3> var3;
    if (var3.size() != 0)
        return false;
    if (var3.n_dimensions() != 3)
        return false;

    evalarray<int, 3> var4;
    if (var4.size() != 0)
        return false;
    if (var4.n_dimensions() != 3)
        return false;

    return true;
}

ADD_TEST(ConstructWithDims)
{
    evalarray a({1u, 2u, 3u}, 1);
    if (!std::is_same_v<decltype(a), evalarray<int,3>>)
        return false;
    if (a.size() != 6)
        return false;
    for (size_t i = 0, size = a.size(); i < size; ++i)
        if (a.data()[i] != 1)
            return false;

    evalarray b({1u, 2u, 3u}, 2.0);
    if (!std::is_same_v<decltype(b), evalarray<double,3>>)
        return false;
    if (b.size() != 6)
        return false;
    for (size_t i = 0, size = b.size(); i < size; ++i)
        if (b.data()[i] != 2.0)
            return false;

    const float val = 2.0;
    evalarray c({1u, 2u, 3u}, val);
    if (!std::is_same_v<decltype(c), evalarray<float,3>>)
        return false;
    if (c.size() != 6)
        return false;
    for (size_t i = 0, size = c.size(); i < size; ++i)
        if (c.data()[i] != 2.0)
            return false;

    const unsigned val2 = 2;
    evalarray d({1u, 2u, 3u}, std::move(val2));
    if (!std::is_same_v<decltype(d), evalarray<unsigned,3>>)
        return false;
    if (d.size() != 6)
        return false;
    for (size_t i = 0, size = d.size(); i < size; ++i)
        if (d.data()[i] != 2)
            return false;

    evalarray e({1, 0, 1}, 1);
    if (!std::is_same_v<decltype(e), evalarray<int,3>>)
        return false;
    if (e.size() != 0)
        return false;

    try {
        evalarray f({1, -1, 1}, 1);
        return false;
    } catch (std::runtime_error err) {
    } catch (...) {
        return false;
    }

    return true;
}

ADD_TEST(ContainerConstruction)
{
    evalarray a{std::array{1, 2, 3 ,4}};
    if (!std::is_same_v<decltype(a), evalarray<int, 1>>)
        return false;
    if (a.dimensions() != std::array<size_t, 1>{4u})
        return false;

    evalarray b{std::array{std::array{1, 2, 3}, std::array{1, 2, 3}}};
    if (!std::is_same_v<decltype(b), evalarray<int, 2>>)
        return false;
    if (b.dimensions() != std::array<size_t, 2>{2u, 3u})
        return false;

    return true;
}

ADD_TEST(AccessOperators)
{
    evalarray a({3, 3, 3}, 2);
    try {
        a(3, 3, 3);
        return false;
    } catch (std::runtime_error err) {
    } catch (...) {
        return false;
    }

    try {
        a(-1, 2, 2);
        return false;
    } catch (std::runtime_error err) {
    } catch (...) {
        return false;
    }

    auto& elem = a(2, 1, 2);
    if (elem != 2)
        return false;

    elem = 3;
    if (a.data()[23] != 3)
        return false;
    if (a(2, 1, 2) != 3)
        return false;

    a(1, 1, 2) = 5;
    if (a(2, 1, 2) != 3)
        return false;
    if (a(1, 1, 2) != 5)
        return false;
    if (a.data()[14] != 5)
        return false;

    evalarray b({1, 0, 1}, 4);
    try {
        b(0, 0, 0);
        return false;
    } catch (std::runtime_error err) {
    } catch (...) {
        return false;
    }

    return true;
}
