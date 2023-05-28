
#include "classmocker.h"

#include <gtest/gtest.h>

namespace OpenGMocker
{

    class ClassMockerTests : public ::testing::Test
    {
    protected:
        ClassMockerTests() = default;
    };

    TEST_F(ClassMockerTests, ConstructsWithoutThrowing)
    {
        EXPECT_NO_THROW(ClassMocker mocker);
    }
}