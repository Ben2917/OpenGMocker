
#ifndef MOCKCLASSMOCKER_H
#define MOCKCLASSMOCKER_H

#include "iclassmocker.h"

#include <gmock/gmock.h>

namespace OpenGMocker
{
    class MockClassMocker : public IClassMocker
    {
    public:
        MOCK_METHOD(std::string, MockClass, (const std::string& class_), (override));
        MOCK_METHOD(std::string, GetClassName, (), (const, override));
    };
}

#endif // MOCKCLASSMOCKER_H