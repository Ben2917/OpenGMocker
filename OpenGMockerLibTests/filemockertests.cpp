
#include "filemocker.h"

#include <gtest/gtest.h>

namespace OpenGMocker
{
    class FileMockerTests : public ::testing::Test
    {
    protected:
        FileMockerTests() = default;
    };

    TEST_F(FileMockerTests, ConstructsWithoutThrowing)
    {
        EXPECT_NO_THROW(FileMocker mocker);
    }
}