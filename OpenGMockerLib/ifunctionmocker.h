
#ifndef IFUNCTIONMOCKER_H
#define IFUNCTIONMOCKER_H

#include "mockerexception.h"

#include <exception>
#include <string>

namespace OpenGMocker
{
    MOCKER_EXCEPTION(FunctionMockerException)

    class IFunctionMocker
    {
    public:
        virtual ~IFunctionMocker() = default;

        virtual std::string MockFunction(const std::string& function) = 0;

    };

}

#endif // IFUNCTIONMOCKER_H