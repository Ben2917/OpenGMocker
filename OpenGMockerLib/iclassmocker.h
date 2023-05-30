
#ifndef ICLASSMOCKER_H
#define ICLASSMOCKER_H

#include "mockerexception.h"

#include <string>

namespace OpenGMocker
{
    MOCKER_EXCEPTION(ClassMockerException)

    class IClassMocker
    {
    public:
        virtual ~IClassMocker() = default;

        virtual std::string MockClass(const std::string& class_) = 0;
        virtual std::string GetClassName() const = 0;
    };

}

#endif // ICLASSMOCKER_H
