
#ifndef FILEMOCKER_H
#define FILEMOCKER_H

#include "ifilemocker.h"
#include "iclassmocker.h"

#include <memory>

namespace OpenGMocker
{
    class FileMocker : public IFileMocker 
    {
    public:
        struct Settings
        {
            bool useCompatiblityGuards = true;
        };

        FileMocker(std::unique_ptr<IClassMocker> classMocker_, const Settings &settings_);

        void MockFile(const std::string& inputFilename, const std::string& outputFilename);
        std::string MockFileContent(const std::string& fileContent_);

    private:
        std::unique_ptr<IClassMocker> classMocker;
        Settings settings;
        std::string fileContent;
    };
}

#endif // FILEMOCKER_H