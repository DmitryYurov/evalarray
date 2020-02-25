#include "evalarray.h"
#include "ITest.h"

using namespace Eval;

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
