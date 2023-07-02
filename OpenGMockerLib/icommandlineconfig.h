
#ifndef ICOMMANDLINECONFIG_H
#define ICOMMANDLINECONFIG_H

#include <memory>
#include <string>

namespace OpenGMocker
{
    class ICommandLineConfig
    {
    public:
        virtual ~ICommandLineConfig() = default;

        enum class TabsOrSpaces
        {
            Tabs,
            Spaces
        };

        enum class PragmaOrIfndef
        {
            Pragma,
            Ifndef
        };

        static std::unique_ptr<ICommandLineConfig> CreateDefault();

        [[nodiscard]] virtual TabsOrSpaces GetTabsOrSpaces() const = 0;
        [[nodiscard]] virtual int GetTabSpaces() const = 0;
        [[nodiscard]] virtual std::string GetOverriddenMockClassName() const = 0;
        [[nodiscard]] virtual PragmaOrIfndef GetPragmaOrIfndef() const = 0;

    };
}

#endif // ICOMMANDLINECONFIG_H