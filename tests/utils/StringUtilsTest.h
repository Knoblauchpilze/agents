#ifndef STRINGUTILSTEST_H
#define STRINGUTILSTEST_H

#include <iostream>
#include "StringUtils.h"

namespace utils {
    namespace strings {
        namespace tests {

            class StringUtilsTest
            {
                public:

                    StringUtilsTest();

                    ~StringUtilsTest();

                    void test() const;

                protected:

                    bool testInt() const;

                    bool testUInt() const;

                    bool testFloat() const;

                    bool testDouble() const;

                    bool testString() const;

                private:
            };

        }
    }
}

#endif // STRINGUTILSTEST_H
