#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <iostream>
#include <string>

namespace utils
{
    namespace strings
    {

        template <typename ValueType>
        class StringUtils
        {
            public:

                StringUtils(const std::string& value);

                ~StringUtils();

                ValueType asValue() const;

            protected:

            private:

                std::string m_value;
        };

    }
}

#include "StringUtils.hxx"

#endif // STRINGUTILS_H
