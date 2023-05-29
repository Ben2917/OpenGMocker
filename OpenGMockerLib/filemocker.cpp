
#include "filemocker.h"

#include <algorithm>
#include <sstream>

namespace OpenGMocker
{
    FileMocker::FileMocker(std::unique_ptr<IClassMocker> classMocker_, const Settings &settings_) :
        classMocker(std::move(classMocker_)),
        settings(settings_)
    {
    }

    void FileMocker::MockFile(const std::string& inputFilename, const std::string& outputFilename)
    {
    }

    std::string FileMocker::MockFileContent(const std::string& fileContent_)
    {
        fileContent = fileContent_;
        // Check for namespace
        const auto namespaceName = [this] () -> std::string
        {
            size_t namespacePos = std::string::npos;
            if ((namespacePos = fileContent.find("namespace")) != std::string::npos)
            {
                // We have a namespace, save its name so the mock can be added to it

                const auto openingBracePos = fileContent.find_first_of('{');
                const auto namespaceName = fileContent.substr(namespacePos, openingBracePos - namespacePos);
                fileContent = fileContent.substr(openingBracePos + 1, fileContent.size() - (openingBracePos + 1));
                return namespaceName;
            }
            return {};
        }();

        // Rip out the class regardless of namespace
        size_t classPos = std::string::npos;
        if ((classPos = fileContent.find("class")) != std::string::npos)
        {

        }

        std::string mockClassName;
        std::for_each(
            mockClassName.begin(), 
            mockClassName.end(), 
            [] (char& c) 
            { 
                c = std::toupper(c); 
            });

        std::stringstream mockFileStream;
        if (settings.useCompatiblityGuards)
        {
            mockFileStream
                << "#ifndef " << mockClassName << "_H\n"
                << "#define " << mockClassName << "_H\n";
        }
        else
        {
            mockFileStream << "#pragma once\n";
        }


        if (settings.useCompatiblityGuards)
        {
            mockFileStream << "#endif //" << mockClassName;
        }
        return mockFileStream.str();
    }
}