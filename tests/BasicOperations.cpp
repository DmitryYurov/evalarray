#include "evalarray.h"
#include "ITest.h"

using namespace Eval;

ADD_TEST(DefaultConstructor) {
    evalarray<double> var;
    if (var.size() != 0)
        return false;
    if (var.nDims() != 1)
        return false;

    evalarray<int> var2;
    if (var2.size() != 0)
        return false;
    if (var2.nDims() != 1)
        return false;

    evalarray<double, 3> var3;
    if (var3.size() != 0)
        return false;
    if (var3.nDims() != 3)
        return false;

    evalarray<int, 3> var4;
    if (var4.size() != 0)
        return false;
    if (var4.nDims() != 3)
        return false;

    return true;
}

ADD_TEST(MakeEvalarray) {
    auto array = make_evalarray<double>();
    if (array.size() != 0)
        return false;
    if (array.nDims() != 1)
        return false;

    auto array2 = make_evalarray<int>();
    if (array2.size() != 0)
        return false;
    if (array2.nDims() != 1)
        return false;

    auto array3 = make_evalarray<double>(1u, 2u, 3u);
    if (array3.size() != 6u)
        return false;
    if (array3.nDims() != 3)
        return false;

    auto array4 = make_evalarray<int>(1u, 2u, 3u);
    if (array4.size() != 6u)
        return false;
    if (array4.nDims() != 3)
        return false;

    return true;
}

ADD_TEST(ContructWithDims)
{
    evalarray a(1, {1u, 2u, 3u});
    return true;
}
