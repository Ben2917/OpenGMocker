
#ifndef CLASSMOCKER_H
#define CLASSMOCKER_H

#include "iclassmocker.h"
#include "ifunctionmocker.h"

#include <memory>
#include <vector>

namespace OpenGMocker
{
    class ClassMocker : public IClassMocker
    {
    public:
        ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_);
        virtual ~ClassMocker() = default;

        std::string MockClass(const std::string& class_) override;

    private:
        std::string GetInterfaceName();
        std::string GetStrippedFunctions();
        std::vector<std::string> GetMockableFunctions(std::string strippedFunctions);

        std::unique_ptr<IFunctionMocker> functionMocker;
        std::string classStr;
    };
}
#endif // CLASSMOCKER_H