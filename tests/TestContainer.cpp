#include "TestContainer.h"
#include "ITest.h"

std::vector<std::unique_ptr<ITest>>& TestContainer::tests()
{
    static std::vector<std::unique_ptr<ITest>> all_tests;
    return all_tests;
}

void TestContainer::addTest(std::unique_ptr<ITest> test)
{
    tests().push_back(std::move(test));
}
