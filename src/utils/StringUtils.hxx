
#include "StringUtils.h"

namespace utils
{
    namespace strings
    {

        template <typename ValueType>
        StringUtils<ValueType>::StringUtils(const std::string& value):
            m_value(value)
        {
            // Nothing to do.
        }

        template <typename ValueType>
        StringUtils<ValueType>::~StringUtils()
        {
            // Nothing to do.
        }

        template <> int StringUtils<int>::asValue() const;

        template <> unsigned int StringUtils<unsigned int>::asValue() const;

        template <> float StringUtils<float>::asValue() const;

        template <> double StringUtils<double>::asValue() const;

        template <> std::string StringUtils<std::string>::asValue() const;

    }
}
