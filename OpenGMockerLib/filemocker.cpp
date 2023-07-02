
#include "filemocker.h"

#include "commandlineconfig.h"
#include "utilities.h"

#include <algorithm>
#include <fstream>
#include <ranges>
#include <sstream>

namespace OpenGMocker
{
    FileMocker::FileMocker(std::unique_ptr<IClassMocker> classMocker_, 
        const std::shared_ptr<ICommandLineConfig> &commandLineConfig_) :
        classMocker(std::move(classMocker_)),
        commandLineConfig(commandLineConfig_)
    {
    }

    void FileMocker::MockFile(const std::string& inputFilename, const std::string& outputFilename)
    {
        std::stringstream inputFileBuffer;
        std::ifstream inputFile(inputFilename);
        if (!(inputFile.good() && inputFile.is_open()))
        {
            throw FileMockerException("Failed to open input file");
        }

        inputFileBuffer << inputFile.rdbuf();
        const auto mockedFileContent = MockFileContent(inputFileBuffer.str());

        std::ofstream outputFile(outputFilename);
        if (!(outputFile.good() && outputFile.is_open()))
        {
            throw FileMockerException("Failed to open output file");
        }
        
        outputFile.write(mockedFileContent.c_str(), mockedFileContent.size());
        outputFile.close();
    }

    std::string FileMocker::MockFileContent(const std::string& fileContent_)
    {
        fileContent = fileContent_;
        
        const auto namespaceName = ParseNamespace();
        const auto mockedClass = ParseAndMockClass();

        const auto upperClassName = ToUpper(classMocker->GetClassName());
        const auto lowerClassName = ToLower(upperClassName);

        const bool useCompatGuards = commandLineConfig->GetPragmaOrIfndef() == CommandLineConfig::PragmaOrIfndef::Ifndef;
        
        std::stringstream mockFileStream;
        if (useCompatGuards)
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
            << "\n";

        if (namespaceName)
        {
            mockFileStream << "namespace " << *namespaceName << "\n"
                << "{\n";
        }

        mockFileStream << mockedClass;

        if (namespaceName)
        {
            mockFileStream << "}\n";
        }

        mockFileStream << "\n";

        if (useCompatGuards)
        {
            mockFileStream << "#endif // MOCK" << upperClassName << "_H";
        }
        return mockFileStream.str();
    }

    std::optional<std::string> FileMocker::ParseNamespace()
    {
        size_t namespacePos = std::string::npos;
        if ((namespacePos = fileContent.find("namespace")) != std::string::npos)
        {
            namespacePos += std::string("namespace").size() + 1;
            
            const auto openingBracePos = fileContent.find_first_of('{');
            auto namespaceName = fileContent.substr(namespacePos, openingBracePos - namespacePos);
            namespaceName.erase(
                std::remove_if(
                    namespaceName.begin(), 
                    namespaceName.end(), 
                    [](char c) 
                    { 
                        return c == '\n'; 
                    }), 
                    namespaceName.end());

            const auto closingBracePos = fileContent.find_last_of('}');
            fileContent = fileContent.substr(openingBracePos + 1, closingBracePos - (openingBracePos + 1));
            return namespaceName;
        }
        return {};
    }

    std::string FileMocker::ParseAndMockClass()
    {
        if (const auto classPos = fileContent.find("class"); classPos != std::string::npos)
        {
            if (const auto classSemicolonPos = fileContent.find_last_of(";"); classSemicolonPos != std::string::npos)
            {
                return classMocker->MockClass(fileContent.substr(classPos, classSemicolonPos + 2 - classPos));
            }
            else
            {
                throw FileMockerException("Failed to find ';' at the end of class");
            }
        }
        else
        {
            throw FileMockerException("Failed to find 'class' in file");
        }
        return {};
    }
}