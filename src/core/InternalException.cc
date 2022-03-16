
#include "InternalException.h"

namespace core
{
    namespace exceptions
    {

        InternalException::InternalException(const std::string& message):
            std::exception(),
            m_message(message),
            m_cause()
        {
            // Nothing to do.
        }

        InternalException::InternalException(const std::string& message, const std::string& cause):
            std::exception(),
            m_message(message),
            m_cause(cause)
        {
            // Nothing to do.
        }

        InternalException::InternalException(const std::string& message, const InternalException& cause):
            std::exception(),
            m_message(message),
            m_cause(cause.what())
        {
            if (cause.hasCause())
            {
                m_cause += ("caused by: " + cause.getCause());
            }
        }

        InternalException::~InternalException()
        {
            // Nothing to do.
        }

        const char* InternalException::what() const noexcept
        {
            return m_message.c_str();
        }

        const std::string& InternalException::getCause() const
        {
            return m_cause;
        }

        bool InternalException::hasCause() const
        {
            return (!m_cause.empty());
        }
    }
}
