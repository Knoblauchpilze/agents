
#include <limits>
#include <cmath>
#include "StringUtilsTest.h"

namespace utils
{
    namespace strings
    {
        namespace tests
        {

            template <typename ValueType>
            bool equal(const ValueType& value1, const ValueType& value2, const ValueType& tolerance)
            {
                return (std::abs(value1 - value2) < tolerance);
            }

            StringUtilsTest::StringUtilsTest()
            {
                // Nothing to do.
            }

            StringUtilsTest::~StringUtilsTest()
            {
                // Nothing to do.
            }

            void StringUtilsTest::test() const
            {
                if (!testInt())
                {
                    std::cerr << "[ERROR] String utils could not convert int" << std::endl;
                }
                if (!testUInt())
                {
                    std::cerr << "[ERROR] String utils could not convert unsigned int" << std::endl;
                }
                if (!testFloat())
                {
                    std::cerr << "[ERROR] String utils could not convert float" << std::endl;
                }
                if (!testDouble())
                {
                    std::cerr << "[ERROR] String utils could not convert double" << std::endl;
                }
                if (!testString())
                {
                    std::cerr << "[ERROR] String utils could not convert string" << std::endl;
                }
            }

            //===========

            bool StringUtilsTest::testInt() const
            {
                const std::string testValue("-32");
                utils::strings::StringUtils<int> wrapper(testValue);
                return (wrapper.asValue() == -32);
            }

            bool StringUtilsTest::testUInt() const
            {
                const std::string testValue("32");
                utils::strings::StringUtils<unsigned int> wrapper(testValue);
                return (wrapper.asValue() == 32);
            }

            bool StringUtilsTest::testFloat() const
            {
                const std::string testValue("32.04");
                utils::strings::StringUtils<float> wrapper(testValue);
                return (equal(wrapper.asValue(), 32.04f, std::numeric_limits<float>::min()));
            }

            bool StringUtilsTest::testDouble() const
            {
                const std::string testValue("-14.056");
                utils::strings::StringUtils<double> wrapper(testValue);
                return (equal(wrapper.asValue(), -14.056, std::numeric_limits<double>::min()));

            }

            bool StringUtilsTest::testString() const
            {
                const std::string testValue("testOption");
                utils::strings::StringUtils<std::string> wrapper(testValue);
                return (wrapper.asValue() == testValue);
            }

        }
    }
}
