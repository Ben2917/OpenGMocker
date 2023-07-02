
#ifndef FILEMOCKER_H
#define FILEMOCKER_H

#include "ifilemocker.h"
#include "iclassmocker.h"

#include <memory>
#include <optional>

namespace OpenGMocker
{
    class ICommandLineConfig;

    class FileMocker : public IFileMocker 
    {
    public:
        FileMocker(std::unique_ptr<IClassMocker> classMocker_, 
            const std::shared_ptr<ICommandLineConfig> &commandLineConfig_);

        void MockFile(const std::string& inputFilename, const std::string& outputFilename);
        std::string MockFileContent(const std::string& fileContent_);

    private:
        std::optional<std::string> ParseNamespace();
        std::string ParseAndMockClass();


        std::unique_ptr<IClassMocker> classMocker;
        std::shared_ptr<ICommandLineConfig> commandLineConfig;

        std::string fileContent;
    };
}

#endif // FILEMOCKER_H