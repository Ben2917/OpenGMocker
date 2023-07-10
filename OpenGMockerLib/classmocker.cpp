
#include "classmocker.h"

#include "commandlineconfig.h"

#include <algorithm>
#include <sstream>

namespace OpenGMocker
{
    ClassMocker::ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_, 
        const std::shared_ptr<ICommandLineConfig> &commandLineConfig_) :
        functionMocker(std::move(functionMocker_)),
        commandLineConfig(commandLineConfig_)
    {
    }

    std::string ClassMocker::MockClass(const std::string& class_)
    {
        classStr = class_;

        const auto name = GetInterfaceName();
        const auto functions = GetStrippedFunctions();
        const auto tabConstant = GetTabConstant();

        const auto overriddenClassName = commandLineConfig->GetOverriddenMockClassName();

        std::stringstream mockClassStream;
        mockClassStream
            << "class Mock" << (!overriddenClassName.empty() ? overriddenClassName : name) << " : public " << name << "\n"
            << "{\n"
            << "public:\n";
        for (const auto& function : functions)
        {
            mockClassStream << tabConstant << functionMocker->MockFunction(function) << "\n";
        }
        mockClassStream << "};\n";
        className = name;
        return mockClassStream.str();
    }

    std::string ClassMocker::GetClassName() const
    {
        if (className.empty())
        {
            throw ClassMockerException("No class name found. Have you called \"MockClass\" first?");
        }

        return className;
    }
    
    std::string ClassMocker::GetInterfaceName()
    {
        const auto whitespacePos = classStr.find_first_of(' ');
        const auto openingBracePos = classStr.find_first_of('{');
        std::string name = classStr.substr(whitespacePos, openingBracePos - whitespacePos);
        name.erase(
            std::remove_if(
                name.begin(), 
                name.end(), 
                [] (char c) 
                { 
                    return c == '\n' || c == ' '; 
                }), 
            name.end());
        classStr = classStr.substr(openingBracePos + 1, classStr.size() - (openingBracePos + 1));
        return name;
    }
    
    std::vector<std::string> ClassMocker::GetStrippedFunctions()
    {
        std::vector<std::string> pureVirtualFunctions;

        const auto closingBracePos = classStr.find_last_of('}');
        std::string classBody = classStr.substr(0, closingBracePos);

        // Extract functions
        size_t functionStart = 0;
        while ((functionStart = classBody.find("virtual")) != std::string::npos)
        {
            const auto functionEnd = [&classBody, functionStart]
            {
                const auto end = classBody.find(";", functionStart);
                if (end == std::string::npos)
                {
                    throw ClassMockerException("Found start of function but not end");
                }
                return end + 1;
            }();

            const auto function = classBody.substr(functionStart, functionEnd - functionStart);
            if (function.find('~') == std::string::npos)
            {
                pureVirtualFunctions.push_back(function);
            }

            classBody = classBody.substr(functionEnd, classBody.size() - functionEnd);
        }
        return pureVirtualFunctions;
    }

    std::string ClassMocker::GetTabConstant() const
    {
        switch (commandLineConfig->GetTabsOrSpaces())
        {
        case ICommandLineConfig::TabsOrSpaces::Tabs:
            return "\t";
        case ICommandLineConfig::TabsOrSpaces::Spaces:
        {
            const auto tabSpaceCount = commandLineConfig->GetTabSpaces();
            std::string tabSpace;
            for (int i = 0; i < tabSpaceCount; i++)
            {
                tabSpace += " ";
            }
            return tabSpace;
        }
        default:
            throw std::runtime_error("Unknown tab or space option");
        }
    }
}