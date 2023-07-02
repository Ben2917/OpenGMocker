
#include "commandlineconfig.h"

#include <gtest/gtest.h>

namespace OpenGMocker
{

    class CommandLineConfigTests : public ::testing::Test
    {
    protected:
        CommandLineConfigTests() = default;
    };

    TEST_F(CommandLineConfigTests, ConstructsWithoutThrowing)
    {
        EXPECT_NO_THROW(CommandLineConfig defaultConfig());
        EXPECT_NO_THROW(CommandLineConfig withArgsConfig(std::vector<std::string>()));
    }

    TEST_F(CommandLineConfigTests, CanParseValidTabsOrSpaces)
    {
        const auto TabsConfig = std::vector<std::string>
        {
            "-tabsOrSpaces", "tabs"
        };

        std::unique_ptr<CommandLineConfig> config;
        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(TabsConfig));
        ASSERT_EQ(config->GetTabsOrSpaces(), CommandLineConfig::TabsOrSpaces::Tabs);

        const auto SpacesConfig = std::vector<std::string>
        {
            "-tabsOrSpaces", "spaces"
        };

        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(SpacesConfig));
        ASSERT_EQ(config->GetTabsOrSpaces(), CommandLineConfig::TabsOrSpaces::Spaces);
    }

    TEST_F(CommandLineConfigTests, ThrowsOnNoSecondArgumentTabsOrSpaces)
    {
        const auto NoSecondArgConfig = std::vector<std::string>
        {
            "-tabsOrSpaces"
        };

        EXPECT_THROW(CommandLineConfig config(NoSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, ThrowsOnInvalidSecondArgumentTabsOrSpaces)
    {
        const auto InvalidSecondArgConfig = std::vector<std::string>
        {
            "-tabsOrSpaces", "INVALID"
        };

        EXPECT_THROW(CommandLineConfig config(InvalidSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, CanParseValidTabSpaceCount)
    {
        const auto TabSpaceCountTwo = std::vector<std::string>
        {
            "-tabSpaceCount", "2"
        };

        std::unique_ptr<CommandLineConfig> config;
        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(TabSpaceCountTwo));
        ASSERT_EQ(config->GetTabSpaces(), 2);

        const auto TabSpaceCountFour = std::vector<std::string>
        {
            "-tabSpaceCount", "4"
        };

        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(TabSpaceCountFour));
        ASSERT_EQ(config->GetTabSpaces(), 4);
    }

    TEST_F(CommandLineConfigTests, ThrowsOnNoSecondArgumentTabSpaceCount)
    {
        const auto NoSecondArgConfig = std::vector<std::string>
        {
            "-tabSpaceCount"
        };

        EXPECT_THROW(CommandLineConfig config(NoSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, ThrowsOnInvalidSecondArgumentTabSpaceCount)
    {
        const auto InvalidSecondArgConfig = std::vector<std::string>
        {
            "-tabSpaceCount", "3"
        };

        EXPECT_THROW(CommandLineConfig config(InvalidSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, CanParseValidOverriddenClassName)
    {
        const auto ClassNameConfig = std::vector<std::string>
        {
            "-className", "MockClassName"
        };

        std::unique_ptr<CommandLineConfig> config;
        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(ClassNameConfig));
        ASSERT_EQ(config->GetOverriddenMockClassName(), "MockClassName");
    }

    TEST_F(CommandLineConfigTests, ThrowsOnNoSecondArgumentOverriddenClassName)
    {
        const auto NoSecondArgConfig = std::vector<std::string>
        {
            "-className"
        };

        EXPECT_THROW(CommandLineConfig config(NoSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, CanParseValidPragmaOrIfndef)
    {
        const auto PragmaConfig = std::vector<std::string>
        {
            "-pragmaOrIfndef", "pragma"
        };

        std::unique_ptr<CommandLineConfig> config;
        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(PragmaConfig));
        ASSERT_EQ(config->GetPragmaOrIfndef(), CommandLineConfig::PragmaOrIfndef::Pragma);

        const auto IfndefConfig = std::vector<std::string>
        {
            "-pragmaOrIfndef", "ifndef"
        };

        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(IfndefConfig));
        ASSERT_EQ(config->GetPragmaOrIfndef(), CommandLineConfig::PragmaOrIfndef::Ifndef);
    }

    TEST_F(CommandLineConfigTests, ThrowsOnInvalidSecondArgumentPragmaOrIfndef)
    {
        const auto InvalidSecondArgConfig = std::vector<std::string>
        {
            "-pragmaOrIfndef", "INVALID"
        };

        EXPECT_THROW(CommandLineConfig config(InvalidSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, ThrowsOnNoSecondArgumentPragmaOrIfndef)
    {
        const auto NoSecondArgConfig = std::vector<std::string>
        {
            "-pragmaOrIfndef"
        };

        EXPECT_THROW(CommandLineConfig config(NoSecondArgConfig), std::invalid_argument);
    }

    TEST_F(CommandLineConfigTests, CanParseAllArguments)
    {
        const auto Args = std::vector<std::string>
        {
            "-pragmaOrIfndef", "ifndef",
            "-tabsOrSpaces", "spaces",
            "-tabSpaceCount", "4",
            "-className", "MockClassName"
        };

        std::unique_ptr<CommandLineConfig> config;
        EXPECT_NO_THROW(config = std::make_unique<CommandLineConfig>(Args));

        ASSERT_EQ(config->GetTabsOrSpaces(), CommandLineConfig::TabsOrSpaces::Spaces);
        ASSERT_EQ(config->GetTabSpaces(), 4);
        ASSERT_EQ(config->GetOverriddenMockClassName(), "MockClassName");
        ASSERT_EQ(config->GetPragmaOrIfndef(), CommandLineConfig::PragmaOrIfndef::Ifndef);
    }
}
