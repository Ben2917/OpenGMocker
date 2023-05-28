
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

        std::string MockClass(const std::string& class_) override;
    };
}
#endif // CLASSMOCKER_H