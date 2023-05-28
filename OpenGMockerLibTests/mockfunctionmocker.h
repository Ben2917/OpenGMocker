
#ifndef MOCKFUNCTIONMOCKER_H
#define MOCKFUNCTIONMOCKER_H

#include "ifunctionmocker.h"

#include <gmock/gmock.h>

namespace OpenGMocker
{
    class MockFunctionMocker : public IFunctionMocker
    {
    public:
        MOCK_METHOD(std::string, MockFunction, (const std::string& function), (override));
    };
}

#endif // MOCKFUNCTIONMOCKER_H
