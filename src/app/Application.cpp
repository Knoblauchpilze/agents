
#include "Application.h"
#include "InternalException.h"

namespace application {

    Application::Application(const std::string& name):
        m_name(name),
        m_arguments()
    {
        // Nothing to do.
    }

    Application::~Application()
    {
        // Nothing to do.
    }

    //================

    const std::string& Application::getName() const
    {
        return m_name;
    }

    //================

    void Application::addOption(const core::application::ProgramOptions& option)
    {
        m_arguments.insert(std::make_pair(option.getName(), option));
    }

    void Application::removeOption(const core::application::ProgramOptions& option)
    {
        m_arguments.erase(option.getName());
    }

    const core::application::ProgramOptions& Application::getOption(const std::string& name) const
    {
        std::unordered_map<std::string, core::application::ProgramOptions>::const_iterator option(m_arguments.find(name));
        if (option == m_arguments.cend())
        {
            throw core::exceptions::InternalException(std::string("Could not find option"));
        }
        return option->second;
    }

    //================

    void Application::parseArguments(const std::vector<std::string>& arguments)
    {
        size_t index(0);
        const size_t argumentsCount(arguments.size());
        std::unordered_map<std::string, core::application::ProgramOptions>::iterator currentOption;
        std::vector<std::string> values;
        while(index < argumentsCount)
        {
            const std::string currentArgument(arguments[index]);
            std::unordered_map<std::string, core::application::ProgramOptions>::iterator option(m_arguments.find(currentArgument));
            if (option != m_arguments.end())
            {
                // Flush the current values in the current option
                if (currentOption != m_arguments.end())
                {
                    currentOption->second.setValues(values);
                }
                // Found a new argument, let's fill its values.
                currentOption = option;
                values.clear();
            }
            else
            {
                values.push_back(currentArgument);
            }
            ++index;
        }
        // Append the last option
        if (currentOption != m_arguments.end())
        {
            currentOption->second.setValues(values);
        }
    }

}
