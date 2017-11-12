#ifndef INTERNALEXCEPTION_H
#define INTERNALEXCEPTION_H

#include <iostream>
#include <stdexcept>

namespace core
{
    namespace exceptions
    {
        class InternalException : public std::exception
        {
            public:

                InternalException(const std::string& message);

                InternalException(const std::string& message, const std::string& cause);

                InternalException(const std::string& message, const InternalException& cause);

                virtual ~InternalException();

                virtual const char* what() const noexcept;

                const std::string& getCause() const;

                bool hasCause() const;

            protected:

            private:

                std::string m_message;

                std::string m_cause;
        };
    }
}

#endif // INTERNALEXCEPTION_H
