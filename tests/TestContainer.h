#ifndef TESTRUNNER_H
#define TESTRUNNER_H

#include <memory>
#include <vector>

class ITest;

class TestContainer {
public:
    static std::vector<std::unique_ptr<ITest>>& tests();
    static void addTest(std::unique_ptr<ITest> test);
};

#endif // TESTRUNNER_H
