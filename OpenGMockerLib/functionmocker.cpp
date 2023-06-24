
#include "functionmocker.h"

#include <sstream>

namespace OpenGMocker
{

    FunctionMocker::FunctionMocker() = default;

    FunctionMocker::~FunctionMocker() = default;

    std::string FunctionMocker::MockFunction(const std::string& function_)
    {
        function = function_;
        GetVirtualEnd();
        const auto returnType = GetReturnType();
        const auto functionName = GetFunctionName();
        const auto parsedParams = GetParams();
        const auto constQualified = IsConstQualified();

        std::stringstream mockedFunction;
        mockedFunction
            << "MOCK_METHOD("
            << returnType << ", "
            << functionName << ", "
            << "("
            << parsedParams
            << "), "
            << (constQualified ? "(const, override)" : "(override)")
            << ");";

        return mockedFunction.str();
    }

    void FunctionMocker::GetVirtualEnd()
    {
        if (const auto virtualPos = function.find("virtual"); virtualPos != std::string::npos)
        {
            const auto endOfVirtual = virtualPos + std::string("virtual").size() + 1;
            function = function.substr(endOfVirtual, function.size() - endOfVirtual);
        }
        else
        {
            throw FunctionMockerException("Could not parse \'virtual\'");
        }
    }

    std::string FunctionMocker::GetReturnType()
    {
        if (const auto secondSpacePos = function.find_first_of(' '); 
            secondSpacePos != std::string::npos)
        {
            const auto functionNameStart = secondSpacePos + 1;
            const auto returnType = function.substr(0, secondSpacePos);
            function = function.substr(functionNameStart, function.size() - functionNameStart);
            return returnType;
        }
        else
        {
            throw FunctionMockerException("Could not parse return type");
        }
    }

    std::string FunctionMocker::GetFunctionName()
    {
        if (const auto openParenthesesPos = function.find_first_of('('); openParenthesesPos != std::string::npos)
        {
            const auto functionName = function.substr(0, openParenthesesPos);
            function = function.substr(openParenthesesPos + 1, function.size() - openParenthesesPos);
            return functionName;
        }
        else
        {
            throw FunctionMockerException("Could not find \'(\' in a given function");
        }
    }

    std::string FunctionMocker::GetParams()
    {
        if (const auto closeParenthesesPos = function.find_first_of(')'); closeParenthesesPos != std::string::npos)
        {
            const auto params = function.substr(0, closeParenthesesPos);
            function = function.substr(closeParenthesesPos, function.size() - closeParenthesesPos);
            return params;
        }
        else
        {
            throw FunctionMockerException("Could not find \')\' in a given function");
        }
    }

    bool FunctionMocker::IsConstQualified() const
    {
        const auto qualifiers = function.substr(0, function.size());
        return qualifiers.find("const", 0) != std::string::npos;
    }

}