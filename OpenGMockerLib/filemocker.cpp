
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
                namespacePos += std::string("namespace").size() + 1;
                // We have a namespace, save its name so the mock can be added to it

                const auto openingBracePos = fileContent.find_first_of('{');
                auto namespaceName = fileContent.substr(namespacePos, openingBracePos - namespacePos);
                namespaceName.erase(std::remove_if(namespaceName.begin(), namespaceName.end(), [](char c) { return c == '\n'; }), namespaceName.end());

                const auto closingBracePos = fileContent.find_last_of('}');
                fileContent = fileContent.substr(openingBracePos + 1, closingBracePos - (openingBracePos + 1));
                return namespaceName;
            }
            return {};
        }();

        // Rip out the class regardless of namespace
        const auto mockedClass = [this]() -> std::string
        {
            if (const auto classPos = fileContent.find("class"); classPos != std::string::npos)
            {
                return classMocker->MockClass(fileContent.substr(classPos, fileContent.size() - classPos));
            }
            return {};
        }();

        auto upperClassName = classMocker->GetClassName();
        std::for_each(
            upperClassName.begin(), 
            upperClassName.end(), 
            [] (char& c) 
            { 
                c = std::toupper(c); 
            });
        auto lowerClassName = upperClassName;
        std::for_each(
            lowerClassName.begin(),
            lowerClassName.end(),
            [](char& c)
            {
                c = std::tolower(c);
            });

        std::stringstream mockFileStream;
        if (settings.useCompatiblityGuards)
        {
            mockFileStream
                << "#ifndef MOCK" << upperClassName << "_H\n"
                << "#define MOCK" << upperClassName << "_H\n";
        }
        else
        {
            mockFileStream << "#pragma once\n";
        }

        mockFileStream << "\n"
            << "#include \"" << lowerClassName << ".h\"\n"
            << "#include <gmock/gmock.h>\n"
            << "\n"
            << "namespace " << namespaceName << "\n"
            << "{\n"
            << mockedClass
            << "}\n"
            << "\n";

        if (settings.useCompatiblityGuards)
        {
            mockFileStream << "#endif // MOCK" << upperClassName << "_H";
        }
        return mockFileStream.str();
    }
}