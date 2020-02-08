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
    virtual bool run() = 0;
};

#define ADD_TEST(name) \
class name : public ITest { \
public: \
    ~name() override = default; \
    bool run() override; \
}; \
\
const ITest::AddTestHelper<name> name ## var; \
\
bool name::run()

#endif // ITEST_H_
