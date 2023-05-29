
#ifndef CLASSMOCKER_H
#define CLASSMOCKER_H

#include "iclassmocker.h"
#include "ifunctionmocker.h"

#include <memory>

namespace OpenGMocker
{
    class ClassMocker : public IClassMocker
    {
    public:
        ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_);
        virtual ~ClassMocker() = default;

        std::string MockClass(const std::string& class_) override;


    private:
        std::unique_ptr<IFunctionMocker> functionMocker;
    };
}
#endif // CLASSMOCKER_H