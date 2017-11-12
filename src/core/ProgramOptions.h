#ifndef PROGRAMOPTIONS_H
#define PROGRAMOPTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>

namespace core
{
    namespace application
    {

        class ProgramOptions
        {
            public:

                ProgramOptions(const std::string& name, bool mandatory = false, const std::string& values = "", const std::string& delimiter = " ");

                virtual ~ProgramOptions();

                bool operator==(const ProgramOptions& other) const;

                const std::string& getName() const;

                bool isFilled() const;

                bool isArray() const;

                bool isMandatory() const;

                const std::string& operator[](const unsigned int& index) const;

                template <typename ValueType>
                ValueType getValueAs(const unsigned int& index) const;

                template <typename ValueType>
                ValueType getValueAs() const;

                void setValues(const std::string& values, const std::string& delimiter = " ");

                void setValues(const std::vector<std::string>& values);

            protected:

                void parseValues(const std::string& values, const std::string& delimiter);

            private:

                std::string m_name;
                std::vector<std::string> m_values;
                bool m_mandatory;
        };

    }
}

#include "ProgramOptions.hxx"

#endif // PROGRAMOPTIONS_H
