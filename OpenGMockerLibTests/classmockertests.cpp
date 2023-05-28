
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

    TEST_F(ClassMockerTests, MockInterfaceDetructorOnly)
    {
        constexpr auto input =
            "class ITestInterface\n"
            "{\n"
            "\tvirtual ~ITestInterface() = default;\n"
            "};";
        constexpr auto expectedOutput =
            "class MockITestInterface : public ITestInterface\n"
            "{\n"
            "};";
        ClassMocker mocker;

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

}