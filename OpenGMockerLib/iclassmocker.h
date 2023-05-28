
#ifndef ICLASSMOCKER_H
#define ICLASSMOCKER_H

#include <string>

namespace OpenGMocker
{

    class IClassMocker
    {
    public:
        virtual ~IClassMocker() = default;

        virtual std::string MockClass(const std::string& class_) = 0;
    };

}

#endif // ICLASSMOCKER_H
