
#include <cmath>
#include "StringUtils.h"

namespace utils {
    namespace strings {

        int convertStringToNumber(const std::string& number)
        {
            int value(0);
            int tenPower(1);
            int index(number.size() - 1);
            while (index >= 0)
            {
                const char digit(number[index]);
                if (digit >= '0' && digit <= '9')
                {
                    value += (tenPower * (digit - '0'));
                }
                tenPower *= 10;
                --index;
            }
            return value;
        }

        template <>
        int StringUtils<int>::asValue() const
        {
            int value(convertStringToNumber(m_value));
            if (m_value.find('-') != std::string::npos)
            {
                value = -value;
            }
            return value;
        }

        template <>
        unsigned int StringUtils<unsigned int>::asValue() const
        {
            return convertStringToNumber(m_value);
        }

        template <>
        float StringUtils<float>::asValue() const
        {
            size_t floatingPointOperator(m_value.find('.'));
            if (floatingPointOperator == std::string::npos)
            {
                floatingPointOperator = m_value.find(',');
            }
            float value(0.0f);
            std::string workingValue(m_value);
            if (floatingPointOperator != std::string::npos)
            {
                std::string decimalPart(workingValue.substr(floatingPointOperator + 1, workingValue.size()));
                const int sizeOfDecimalPart(workingValue.size() - 1 - floatingPointOperator);
                value += (1.0f * convertStringToNumber(decimalPart) / std::pow(10.0f, 1.0f * sizeOfDecimalPart));
                workingValue = workingValue.substr(0, floatingPointOperator);
            }
            value += (1.0f * convertStringToNumber(workingValue));
            if (m_value.find('-') != std::string::npos)
            {
                value = -value;
            }
            return value;
        }

        template <>
        double StringUtils<double>::asValue() const
        {
            size_t floatingPointOperator(m_value.find('.'));
            if (floatingPointOperator == std::string::npos)
            {
                floatingPointOperator = m_value.find(',');
            }
            double value(0.0);
            std::string workingValue(m_value);
            if (floatingPointOperator != std::string::npos)
            {
                std::string decimalPart(workingValue.substr(floatingPointOperator + 1, workingValue.size()));
                const int sizeOfDecimalPart(workingValue.size() - 1 - floatingPointOperator);
                value += (1.0 * convertStringToNumber(decimalPart) / std::pow(10.0, 1.0 * sizeOfDecimalPart));
                workingValue = workingValue.substr(0, floatingPointOperator);
            }
            value += (1.0 * convertStringToNumber(workingValue));
            if (m_value.find('-') != std::string::npos)
            {
                value = -value;
            }
            return value;
        }

        template <>
        std::string StringUtils<std::string>::asValue() const
        {
            return m_value;
        }

    }
}
