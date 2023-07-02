
#ifndef COMMANDLINECONFIG_H
#define COMMANDLINECONFIG_H

#include "icommandlineconfig.h"

#include <vector>

namespace OpenGMocker
{
    class CommandLineConfig : public ICommandLineConfig
    {
    public:
        CommandLineConfig();
        CommandLineConfig(const std::vector<std::string> &commandLineArgs);

        [[nodiscard]] TabsOrSpaces GetTabsOrSpaces() const override;
        [[nodiscard]] int GetTabSpaces() const override;
        [[nodiscard]] std::string GetOverriddenMockClassName() const override;
        [[nodiscard]] PragmaOrIfndef GetPragmaOrIfndef() const override;

    private:
        void ParseCommandLineArgs(const std::vector<std::string>& commandLineArgs);


        TabsOrSpaces tabsOrSpaces;
        int tabSpaces;
        std::string overriddenMockClassName;
        PragmaOrIfndef pragmaOrIfdef;
    };
}

#endif // COMMANDLINECONFIG_H