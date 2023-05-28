
#ifndef IFUNCTIONMOCKER_H
#define IFUNCTIONMOCKER_H

#include <string>

namespace OpenGMocker
{

    class IFunctionMocker
    {
    public:
        virtual ~IFunctionMocker() = default;

        virtual std::string MockFunction(const std::string& function) = 0;

    };

}

#endif // IFUNCTIONMOCKER_H