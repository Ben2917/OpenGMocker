
#include "OpenGMocker.h"

#include <sstream>
#include <stdexcept>
#include <vector>

OpenGMocker::OpenGMocker() = default;

OpenGMocker::~OpenGMocker() = default;

std::string OpenGMocker::MockFunction(const std::string& function)
{
    // Get virtual
    auto firstSpacePos = function.find_first_of(' ');
    const auto virtualIndicator = function.substr(0, firstSpacePos);
    if (virtualIndicator != "virtual")
    {
        throw std::logic_error("Function is not virtual");
    }
    firstSpacePos += 1;

    // Get return type
    const auto secondSpacePos = function
        .substr(firstSpacePos, function.size() - firstSpacePos)
        .find_first_of(' ');
    const auto returnType = function.substr(firstSpacePos, secondSpacePos);

    // Get function name
    const auto openParenthesesPos = function.find_first_of('(');
    const auto functionNameStart = firstSpacePos + secondSpacePos + 1;
    const auto functionName = function.substr(functionNameStart, openParenthesesPos - functionNameStart);

    // Get params
    const auto closeParenthesesPos = function.find_first_of(')');
    const auto params = function.substr(openParenthesesPos, closeParenthesesPos - openParenthesesPos);
    std::vector<std::string> parsedParams; // TODO: Parse params
    
    // Get function qualifiers
    const auto qualifiers = function.substr(closeParenthesesPos, function.size() - closeParenthesesPos);
    const auto constQualified = qualifiers.find("const", 0) != std::string::npos;
    
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
