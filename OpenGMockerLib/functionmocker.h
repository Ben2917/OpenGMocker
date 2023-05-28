
#ifndef FUNCTIONMOCKER_H
#define FUNCTIONMOCKER_H

#include "ifunctionmocker.h"

#include <string>
#include <vector>

namespace OpenGMocker
{

    class FunctionMocker : public IFunctionMocker
    {
    public:
        FunctionMocker();
        ~FunctionMocker() override;

        std::string MockFunction(const std::string& function_) override;

    private:
        void GetVirtualEnd();
        std::string GetReturnType();
        std::string GetFunctionName();
        std::string GetParams();
        bool IsConstQualified() const;

        std::string function;

    };

}
#endif // FUNCTIONMOCKER_H