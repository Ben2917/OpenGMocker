
#include "OpenGMocker.h"

#include <gtest/gtest.h>

class OpenGMockerTests : public ::testing::Test
{
public:
    OpenGMockerTests() = default;
};

TEST_F(OpenGMockerTests, ConstructsWithoutThrowing)
{
    EXPECT_NO_THROW(OpenGMocker mocker);
}