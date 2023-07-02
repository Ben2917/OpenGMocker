
#ifndef CLASSMOCKER_H
#define CLASSMOCKER_H

#include "iclassmocker.h"
#include "ifunctionmocker.h"

#include <memory>
#include <vector>

namespace OpenGMocker
{
    class ICommandLineConfig;

    class ClassMocker : public IClassMocker
    {
    public:
        ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_, 
            const std::shared_ptr<ICommandLineConfig> &commandLineConfig_);
        virtual ~ClassMocker() = default;

        std::string MockClass(const std::string& class_) override;
        std::string GetClassName() const override;

    private:
        std::string GetInterfaceName();
        std::vector<std::string> GetStrippedFunctions();

        std::unique_ptr<IFunctionMocker> functionMocker;
        std::shared_ptr<ICommandLineConfig> commandLineConfig;

        std::string classStr;
        std::string className;
    };
}
#endif // CLASSMOCKER_H