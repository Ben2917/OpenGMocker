
#include "classmocker.h"

#include <algorithm>
#include <sstream>
#include <vector>

namespace OpenGMocker
{
    ClassMocker::ClassMocker(std::unique_ptr<IFunctionMocker> functionMocker_) :
        functionMocker(std::move(functionMocker_))
    {
    }

    std::string ClassMocker::MockClass(const std::string& class_)
    {
        const auto whitespacePos = class_.find_first_of(' ');
        const auto openingBracePos = class_.find_first_of('{');
        std::string name = class_.substr(whitespacePos, openingBracePos - whitespacePos);
        name.erase(std::remove_if(name.begin(), name.end(), [](char c) { return c == '\n' || c == ' '; }), name.end());

        const auto closingBracePos = class_.find_first_of('}');
        std::string pureVirtualFunctions = class_.substr(openingBracePos + 1, closingBracePos - (openingBracePos + 1));
        pureVirtualFunctions.erase(
            std::remove_if(
                pureVirtualFunctions.begin(), 
                pureVirtualFunctions.end(), 
                [] (char c) 
                {
                    return c == '\n' || c == '\t'; 
                }), 
            pureVirtualFunctions.end());

        std::vector<std::string> functions;
        size_t semicolonPos = 0;
        while ((semicolonPos = pureVirtualFunctions.find_first_of(';')) != std::string::npos)
        {
            semicolonPos += 1; // Inclusive
            const auto function = pureVirtualFunctions.substr(0, semicolonPos);
            if (function.find('~') == std::string::npos)
            {
                functions.push_back(function);
            }
            pureVirtualFunctions = pureVirtualFunctions.substr(semicolonPos, pureVirtualFunctions.size() - semicolonPos);
        }

        std::stringstream mockClassStream;
        mockClassStream
            << "class Mock" << name << " : public " << name << "\n"
            << "{\n";
        for (const auto& function : functions)
        {
            mockClassStream << "\t" << functionMocker->MockFunction(function) << "\n";
        }
        mockClassStream << "};";

        return mockClassStream.str();
    }
}