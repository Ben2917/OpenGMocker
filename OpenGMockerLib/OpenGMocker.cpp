
#include "OpenGMocker.h"

#include <sstream>

OpenGMocker::OpenGMocker() = default;

OpenGMocker::~OpenGMocker() = default;

std::string OpenGMocker::MockFunction(const std::string& function_)
{
    function = function_;
    const auto firstSpacePos = GetVirtualEnd();
    const auto [returnType, secondSpacePos] = GetReturnType();
    const auto [functionName, openParenthesesPos] = GetFunctionName();
    const auto [parsedParams, closeParenthesesPos] = GetParams();
    const auto constQualified = IsConstQualified();
    
    std::stringstream mockedFunction;
    mockedFunction
        << "MOCK_METHOD("
        << returnType << ", "
        << functionName << ", "
        << "(), "
        << (constQualified ? "(const, override)" : "(override)")
        << ");";

    return mockedFunction.str();
}

size_t OpenGMocker::GetVirtualEnd()
{
    auto firstSpacePos = function.find_first_of(' ');
    const auto virtualIndicator = function.substr(0, firstSpacePos);
    if (virtualIndicator != "virtual")
    {
        throw std::exception("Function is not virtual");
    }
    firstSpacePos += 1;
    function = function.substr(firstSpacePos, function.size() - firstSpacePos);
    return firstSpacePos;
}

OpenGMocker::ValueOffset<std::string> OpenGMocker::GetReturnType()
{
    const auto secondSpacePos = function
        .substr(0, function.size())
        .find_first_of(' ');

    const auto functionNameStart = secondSpacePos + 1;
    const auto returnType = function.substr(0, secondSpacePos);
    function = function.substr(functionNameStart, function.size() - functionNameStart);
    return { returnType, secondSpacePos };
}

OpenGMocker::ValueOffset<std::string> OpenGMocker::GetFunctionName()
{
    const auto openParenthesesPos = function.find_first_of('(');
    const auto functionName = function.substr(0, openParenthesesPos);
    function = function.substr(openParenthesesPos, function.size() - openParenthesesPos);
    return { functionName, openParenthesesPos };
}

OpenGMocker::ValueOffset<std::vector<OpenGMocker::Param>> OpenGMocker::GetParams()
{
    const auto closeParenthesesPos = function.find_first_of(')');
    const auto params = function.substr(0, closeParenthesesPos);
    std::vector<Param> parsedParams; // TODO: Parse params
    function = function.substr(closeParenthesesPos, function.size() - closeParenthesesPos);
    return { parsedParams, closeParenthesesPos };
}

bool OpenGMocker::IsConstQualified() const
{
    const auto qualifiers = function.substr(0, function.size());
    const auto constQualified = qualifiers.find("const", 0) != std::string::npos;
    return constQualified;
}
