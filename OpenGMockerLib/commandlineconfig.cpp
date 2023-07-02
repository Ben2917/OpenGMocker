
#include "commandlineconfig.h"
#include "utilities.h"

#include <functional>
#include <optional>
#include <stdexcept>
#include <unordered_map>

namespace
{
    constexpr auto TwoSpaceTab = 2;
    constexpr auto FourSpaceTab = 4;
}

namespace OpenGMocker
{

    std::unique_ptr<ICommandLineConfig> ICommandLineConfig::CreateDefault()
    {
        return std::make_unique<CommandLineConfig>();
    }

    CommandLineConfig::CommandLineConfig() :
        tabsOrSpaces(TabsOrSpaces::Spaces),
        tabSpaces(TwoSpaceTab),
        pragmaOrIfdef(PragmaOrIfndef::Ifndef)
    {
    }

    CommandLineConfig::CommandLineConfig(const std::vector<std::string>& commandLineArgs) :
        CommandLineConfig()
    {
        ParseCommandLineArgs(commandLineArgs);
    }

    ICommandLineConfig::TabsOrSpaces CommandLineConfig::GetTabsOrSpaces() const
    {
        return tabsOrSpaces;
    }

    int CommandLineConfig::GetTabSpaces() const
    {
        return tabSpaces;
    }

    std::string CommandLineConfig::GetOverriddenMockClassName() const
    {
        return overriddenMockClassName;
    }

    ICommandLineConfig::PragmaOrIfndef CommandLineConfig::GetPragmaOrIfndef() const
    {
        return pragmaOrIfdef;
    }

    void CommandLineConfig::ParseCommandLineArgs(const std::vector<std::string>& commandLineArgs)
    {
        for (size_t argsIndex = 0; argsIndex < commandLineArgs.size(); argsIndex+=2)
        {
            const auto firstArg = ToLower(commandLineArgs.at(argsIndex));
            const auto secondArg = [argsIndex, &commandLineArgs]() -> std::optional<std::string>
            {
                if (argsIndex + 1 < commandLineArgs.size())
                {
                    return commandLineArgs.at(argsIndex + 1);
                }
                return std::nullopt;
            }();

            if (firstArg == "-tabsorspaces")
            {
                if (!secondArg)
                {
                    throw std::invalid_argument("Did not receive second argument to indicate tab/space use");
                }

                if (ToLower(*secondArg) == "tabs")
                {
                    tabsOrSpaces = TabsOrSpaces::Tabs;
                }
                else if (ToLower(*secondArg) == "spaces")
                {
                    tabsOrSpaces = TabsOrSpaces::Spaces;
                }
                else
                {
                    throw std::invalid_argument("Invalid second argument for tabs/spaces selection");
                }
            }
            else if (firstArg == "-tabspacecount")
            {
                if (!secondArg)
                {
                    throw std::invalid_argument("Did not receive second argument to indicate tab space count");
                }

                if (std::stoi(*secondArg) == TwoSpaceTab)
                {
                    tabSpaces = TwoSpaceTab;
                }
                else if (std::stoi(*secondArg) == FourSpaceTab)
                {
                    tabSpaces = FourSpaceTab;
                }
                else
                {
                    throw std::invalid_argument("Invalid second argument for tab space count");
                }
            }
            else if (firstArg == "-classname")
            {
                if (!secondArg)
                {
                    throw std::invalid_argument("Did not receive second argument for overridden class name");
                }

                overriddenMockClassName = *secondArg;
            }
            else if (firstArg == "-pragmaorifndef")
            {
                if (!secondArg)
                {
                    throw std::invalid_argument("Did not receive second argument for pragma/ifndef");
                }

                if (ToLower(*secondArg) == "pragma")
                {
                    pragmaOrIfdef = PragmaOrIfndef::Pragma;
                }
                else if (ToLower(*secondArg) == "ifndef")
                {
                    pragmaOrIfdef = PragmaOrIfndef::Ifndef;
                }
                else
                {
                    throw std::invalid_argument("Invalid second argument for pragma/ifndef");
                }
            }
            else
            {
                throw std::invalid_argument("Received unknown command line argument");
            }
        }
    }

}
