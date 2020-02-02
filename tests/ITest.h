#ifndef ITEST_H_
#define ITEST_H_

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
    virtual int run() = 0;
};

#define ADD_TEST(name) \
class name : public ITest { \
public: \
    ~name() override = default; \
    int run() override; \
}; \
\
const ITest::AddTestHelper<name> name ## var; \
\
int name::run()

#endif // ITEST_H_
