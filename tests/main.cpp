#include <iostream>
#include "TestContainer.h"
#include "ITest.h"

int main(int, char**)
{
    int count = 0; // number of failed test cases
    for (auto& test: TestContainer::tests())
        count += test->run();

    std::cout << count << " tests failed" << std::endl;
    return count;
}
