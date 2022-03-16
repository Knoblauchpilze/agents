
#include "ProgramOptions.h"

namespace core {
    namespace application {

        ProgramOptions::ProgramOptions(const std::string& name, bool mandatory, const std::string& values, const std::string& delimiter):
            m_name(name),
            m_values(),
            m_mandatory(mandatory)
        {
            parseValues(values, delimiter);
        }

        ProgramOptions::~ProgramOptions()
        {
            // Nothing to do.
        }

        //==================

        bool ProgramOptions::operator==(const ProgramOptions& other) const
        {
            return (getName() == other.getName());
        }

        const std::string& ProgramOptions::getName() const
        {
            return m_name;
        }

        bool ProgramOptions::isFilled() const
        {
            return (!m_values.empty());
        }

        bool ProgramOptions::isArray() const
        {
            return (m_values.size() > 1);
        }

        bool ProgramOptions::isMandatory() const
        {
            return m_mandatory;
        }

        const std::string& ProgramOptions::operator[](const unsigned int& index) const
        {
            return m_values.at(index);
        }

        void ProgramOptions::setValues(const std::string& values, const std::string& delimiter)
        {
            parseValues(values, delimiter);
        }

        void ProgramOptions::setValues(const std::vector<std::string>& values)
        {
            m_values = values;
        }

        //==================

        void ProgramOptions::parseValues(const std::string& values, const std::string& delimiter)
        {
            std::string remainingValues(values);
            while (!remainingValues.empty())
            {
                size_t indexOfDelimiter(remainingValues.find(delimiter, 0));
                if (indexOfDelimiter == std::string::npos)
                {
                    m_values.push_back(remainingValues);
                    remainingValues.clear();
                }
                else {
                    const std::string currentValue(remainingValues.substr(0, indexOfDelimiter));
                    m_values.push_back(currentValue);
                    remainingValues.erase(0, indexOfDelimiter);
                }
            }
        }

    }
}
