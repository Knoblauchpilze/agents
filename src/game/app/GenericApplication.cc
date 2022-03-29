
#include "GenericApplication.h"

namespace application
{
    GenericApplication::GenericApplication(const std::string& name, const unsigned int& argumentCount, const char* const arguments[]):
        Application(name),
        m_arguments()
    {
        // Parse arguments.
        initializeArguments(argumentCount, arguments);
    }

    GenericApplication::~GenericApplication()
    {
        // Nothing to do.
    }

    //============

    void GenericApplication::run()
    {
        parseArguments(m_arguments);
        doProcess();
    }

    //============

    void GenericApplication::initializeArguments(const unsigned int& argumentCount, const char* const arguments[])
    {
        for (unsigned int indexArgument = 0 ; indexArgument < argumentCount ; ++indexArgument)
        {
            m_arguments.push_back(arguments[indexArgument]);
        }
    }
}
