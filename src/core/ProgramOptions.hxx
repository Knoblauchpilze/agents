#ifndef PROGRAMOPTIONS_HXX_INCLUDED
#define PROGRAMOPTIONS_HXX_INCLUDED

#include "ProgramOptions.h"
#include "StringUtils.h"

namespace core
{
    namespace application
    {

        template <typename ValueType>
        ValueType ProgramOptions::getValueAs(const unsigned int& index) const
        {
            utils::strings::StringUtils<ValueType> wrapper(operator[](index));
            return wrapper.asValue();
        }

        template <typename ValueType>
        ValueType ProgramOptions::getValueAs() const
        {
            return getValueAs<ValueType>(0u);
        }

    }
}

/// Hash specialization.
namespace std
{
    template <>
    class hash<core::application::ProgramOptions>
    {
        public:

            inline
            size_t operator()(const core::application::ProgramOptions& options) const
            {
                return std::hash<std::string>()(options.getName());
            }

    };
}

#endif // PROGRAMOPTIONS_HXX_INCLUDED
