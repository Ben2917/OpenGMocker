
#include "classmocker.h"

#include <algorithm>
#include <sstream>

namespace OpenGMocker
{
    ClassMocker::ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_) :
        functionMocker(std::move(functionMocker_))
    {
    }

    std::string ClassMocker::MockClass(const std::string& class_)
    {
        classStr = class_;

        const auto name = GetInterfaceName();
        const auto strippedFunctions = GetStrippedFunctions();
        const auto functions = GetMockableFunctions(strippedFunctions);

        std::stringstream mockClassStream;
        mockClassStream
            << "class Mock" << name << " : public " << name << "\n"
            << "{\n"
            << "public:\n";
        for (const auto& function : functions)
        {
            mockClassStream << "\t" << functionMocker->MockFunction(function) << "\n";
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
    
    std::string ClassMocker::GetStrippedFunctions()
    {
        std::string pureVirtualFunctions;

        const auto closingBracePos = classStr.find_last_of('}');
        std::string classBody = classStr.substr(0, closingBracePos);

        // Extract functions
        size_t functionStart = 0;
        while ((functionStart = classBody.find("virtual")) != std::string::npos)
        {
            const auto functionEnd = [&classBody]
            {
                const auto end = classBody.find(";");
                if (end == std::string::npos)
                {
                    throw ClassMockerException("Found start of function but not end");
                }
                return end + 1;
            }();
            pureVirtualFunctions += classBody.substr(functionStart, functionEnd - functionStart);
            classBody = classBody.substr(functionEnd, classBody.size() - functionEnd);
        }
        return pureVirtualFunctions;
    }

    std::vector<std::string> ClassMocker::GetMockableFunctions(std::string strippedFunctions)
    {
        std::vector<std::string> functions;
        size_t semicolonPos = 0;
        while ((semicolonPos = strippedFunctions.find_first_of(';')) != std::string::npos)
        {
            semicolonPos += 1; // Inclusive of ';'
            const auto function = strippedFunctions.substr(0, semicolonPos);
            if (function.find('~') == std::string::npos)
            {
                functions.push_back(function);
            }
            strippedFunctions = strippedFunctions.substr(semicolonPos, strippedFunctions.size() - semicolonPos);
        }
        return functions;
    }
}