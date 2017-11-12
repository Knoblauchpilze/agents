#ifndef GENERICAPPLICATION_H
#define GENERICAPPLICATION_H

#include <iostream>
#include "Application.h"

namespace application
{

    class GenericApplication : public Application
    {
        public:

            GenericApplication(const std::string& name, const unsigned int& argumentCount, const char* const arguments[]);

            virtual ~GenericApplication();

            virtual void run();

        protected:

            virtual void doProcess() = 0;

        private:

            void initializeArguments(const unsigned int& argumentCount, const char* const arguments[]);

        private:

            std::vector<std::string> m_arguments;
    };
}

#endif // GENERICAPPLICATION_H
