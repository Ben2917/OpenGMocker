
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
        enum class SpacesOrTabs
        {
            SPACES,
            TABS
        };

        ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_, SpacesOrTabs spacesOrTabs_=SpacesOrTabs::SPACES);
        virtual ~ClassMocker() = default;

        std::string MockClass(const std::string& class_) override;
        std::string GetClassName() const override;

    private:
        std::string GetInterfaceName();
        std::vector<std::string> GetStrippedFunctions();

        std::unique_ptr<IFunctionMocker> functionMocker;
        SpacesOrTabs spacesOrTabs;

        std::string classStr;
        std::string className;
    };
}
#endif // CLASSMOCKER_H