
#ifndef CLASSMOCKER_H
#define CLASSMOCKER_H

#include "iclassmocker.h"

namespace OpenGMocker
{
    class ClassMocker : public IClassMocker
    {
    public:
        ClassMocker() = default;
        virtual ~ClassMocker() = default;
    };
}
#endif // CLASSMOCKER_H