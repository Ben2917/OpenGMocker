
#include "mockfilegenerator.h"

#include <gtest/gtest.h>

namespace OpenGMocker
{
    class MockFileGeneratorTests : public ::testing::Test
    {
    public:
        MockFileGeneratorTests() = default;

    };

    TEST_F(MockFileGeneratorTests, ConstructsWithoutThrowing)
    {
        EXPECT_NO_THROW(MockFileGenerator fileGenerator);
    }

}