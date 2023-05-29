
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
        auto firstSpacePos = function.find_first_of(' ');
        const auto virtualIndicator = function.substr(0, firstSpacePos);
        if (virtualIndicator != "virtual")
        {
            throw FunctionMockerException("Function is not virtual");
        }
        firstSpacePos += 1;
        function = function.substr(firstSpacePos, function.size() - firstSpacePos);
    }

    std::string FunctionMocker::GetReturnType()
    {
        const auto secondSpacePos = function
            .substr(0, function.size())
            .find_first_of(' ');

        const auto functionNameStart = secondSpacePos + 1;
        const auto returnType = function.substr(0, secondSpacePos);
        function = function.substr(functionNameStart, function.size() - functionNameStart);
        return returnType;
    }

    std::string FunctionMocker::GetFunctionName()
    {
        const auto openParenthesesPos = function.find_first_of('(');
        const auto functionName = function.substr(0, openParenthesesPos);
        function = function.substr(openParenthesesPos + 1, function.size() - openParenthesesPos);
        return functionName;
    }

    std::string FunctionMocker::GetParams()
    {
        const auto closeParenthesesPos = function.find_first_of(')');
        const auto params = function.substr(0, closeParenthesesPos);
        function = function.substr(closeParenthesesPos, function.size() - closeParenthesesPos);
        return params;
    }

    bool FunctionMocker::IsConstQualified() const
    {
        const auto qualifiers = function.substr(0, function.size());
        const auto constQualified = qualifiers.find("const", 0) != std::string::npos;
        return constQualified;
    }

}