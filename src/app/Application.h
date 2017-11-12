#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "ProgramOptions.h"

namespace application {

    class Application
    {
        public:

            Application(const std::string& name);

            virtual ~Application();

            const std::string& getName() const;

            virtual void run() = 0;

        protected:

            void addOption(const core::application::ProgramOptions& option);

            void removeOption(const core::application::ProgramOptions& option);

            const core::application::ProgramOptions& getOption(const std::string& name) const;

            void parseArguments(const std::vector<std::string>& arguments);

        private:

            std::string m_name;

            std::unordered_map<std::string, core::application::ProgramOptions> m_arguments;
    };

}

#endif // APPLICATION_H
