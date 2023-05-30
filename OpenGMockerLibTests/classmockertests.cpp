
#include "classmocker.h"

#include "mockfunctionmocker.h"

#include <gtest/gtest.h>

namespace OpenGMocker
{

    class ClassMockerTests : public ::testing::Test
    {
    protected:
        ClassMockerTests() :
            mockFunctionMocker(std::make_unique<MockFunctionMocker>())
        {
        }

        std::unique_ptr<MockFunctionMocker> mockFunctionMocker;
    };

    TEST_F(ClassMockerTests, ConstructsWithoutThrowing)
    {
        EXPECT_NO_THROW(ClassMocker mocker(std::move(mockFunctionMocker)));
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
            "};\n";
        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

    TEST_F(ClassMockerTests, MockInterfaceWithOneFunction)
    {
        constexpr auto input =
            "class ITestInterface\n"
            "{\n"
            "\tvirtual ~ITestInterface() = default;\n"
            "\tvirtual void TestFunction() const = 0;\n"
            "};";
        constexpr auto expectedOutput =
            "class MockITestInterface : public ITestInterface\n"
            "{\n"
            "\tMOCK_METHOD(void, TestFunction, (), (const, override));\n"
            "};\n";
        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void TestFunction() const = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, TestFunction, (), (const, override));"));

        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

}