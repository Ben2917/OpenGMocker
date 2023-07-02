#ifndef MOCKICOMMANDLINECONFIG_H
#define MOCKICOMMANDLINECONFIG_H

#include "icommandlineconfig.h"
#include <gmock/gmock.h>

namespace OpenGMocker
{
class MockCommandLineConfig : public ICommandLineConfig
{
public:
    MOCK_METHOD(TabsOrSpaces, GetTabsOrSpaces, (), (const, override));
    MOCK_METHOD(int, GetTabSpaces, (), (const, override));
    MOCK_METHOD(std::string, GetOverriddenMockClassName, (), (const, override));
    MOCK_METHOD(PragmaOrIfndef, GetPragmaOrIfndef, (), (const, override));
};
}

#endif // MOCKICOMMANDLINECONFIG_H