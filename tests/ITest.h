#ifndef ITEST_H_
#define ITEST_H_

#include <iostream>

#include "TestContainer.h"

class ITest {
public:
    template<class T>
    struct AddTestHelper {
        AddTestHelper() {
            TestContainer::addTest(std::make_unique<T>());
        }
    };

    virtual ~ITest() = default;
    virtual const char* title() const = 0;
    virtual bool run() = 0;

    bool execute()
    {
        std::cout << title() << ": ";
        bool result = run();
        std::cout << (result ? "Ok" : "Failed") << std::endl;

        return result;
    }
};

#define ADD_TEST(name) \
class name : public ITest { \
public: \
    ~name() override = default; \
    const char* title() const override; \
    bool run() override; \
}; \
\
const ITest::AddTestHelper<name> name ## var; \
\
const char* name::title() const {return #name;} \
\
bool name::run()

#endif // ITEST_H_
