
#include "functionmocker.h"

#include <gtest/gtest.h>

namespace OpenGMocker
{

    class FunctionMockerTests : public ::testing::Test
    {
    protected:
        FunctionMockerTests() = default;
    };

    TEST_F(FunctionMockerTests, ConstructsWithoutThrowing)
    {
        EXPECT_NO_THROW(FunctionMocker mocker);
    }

    TEST_F(FunctionMockerTests, GenerateMockFromFunctionPrimitiveReturnNoParamsNoQualifiers)
    {
        constexpr auto Function = "virtual int TestFunction() = 0;";
        constexpr auto ExpectedMock = "MOCK_METHOD(int, TestFunction, (), (override));";
        FunctionMocker mocker;

        std::string actualMock;
        EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

        EXPECT_EQ(ExpectedMock, actualMock);
    }

    TEST_F(FunctionMockerTests, GenerateMockFromFunctionPrimitiveReturnNoParamsConstQualified)
    {
        constexpr auto Function = "virtual int TestFunction() const = 0;";
        constexpr auto ExpectedMock = "MOCK_METHOD(int, TestFunction, (), (const, override));";
        FunctionMocker mocker;

        std::string actualMock;
        EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

        EXPECT_EQ(ExpectedMock, actualMock);
    }

    TEST_F(FunctionMockerTests, MockFunctionThrowsTryingToMockANonVirtualFunction)
    {
        constexpr auto Function = "int TestFunction() = 0;";
        FunctionMocker mocker;

        EXPECT_THROW(mocker.MockFunction(Function), FunctionMockerException);
    }

    TEST_F(FunctionMockerTests, GenerateMockFromFunctionPrimitiveReturnPrimitiveParams)
    {
        constexpr auto Function = "virtual int TestFunction(int first, double second, float third) = 0;";
        constexpr auto ExpectedMock = "MOCK_METHOD(int, TestFunction, (int first, double second, float third), (override));";
        FunctionMocker mocker;

        std::string actualMock;
        EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

        EXPECT_EQ(ExpectedMock, actualMock);
    }

    TEST_F(FunctionMockerTests, GenerateMockFromFunctionNoReturnComplexParams)
    {
        constexpr auto Function = "virtual void TestFunction(std::pair<int, int> coords, const std::vector<std::string> &values) = 0;";
        constexpr auto ExpectedMock = "MOCK_METHOD(void, TestFunction, (std::pair<int, int> coords, const std::vector<std::string> &values), (override));";
        FunctionMocker mocker;

        std::string actualMock;
        EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

        EXPECT_EQ(ExpectedMock, actualMock);
    }

    TEST_F(FunctionMockerTests, GenerateMockFromFunctionComplexReturnNoParams)
    {
        constexpr auto Function = "virtual std::vector<std::string> TestFunction() = 0;";
        constexpr auto ExpectedMock = "MOCK_METHOD(std::vector<std::string>, TestFunction, (), (override));";
        FunctionMocker mocker;

        std::string actualMock;
        EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

        EXPECT_EQ(ExpectedMock, actualMock);
    }

    TEST_F(FunctionMockerTests, ExpectThrowOnMalformedFunctions)
    {
        constexpr auto NoParenthesesInput = "virtual void TestFunction = 0;";
        constexpr auto OnlyOpenParenthesesInput = "virtual void TestFunction( = 0;";
        constexpr auto TotalNonsense = "TotalNonsense";
        constexpr auto EmptyString = "";
        constexpr auto NoReturnType = "virtual TestFunction()=0;";

        FunctionMocker mocker;
        EXPECT_THROW(mocker.MockFunction(NoParenthesesInput), FunctionMockerException);
        EXPECT_THROW(mocker.MockFunction(OnlyOpenParenthesesInput), FunctionMockerException);
        EXPECT_THROW(mocker.MockFunction(TotalNonsense), FunctionMockerException);
        EXPECT_THROW(mocker.MockFunction(EmptyString), FunctionMockerException);
        EXPECT_THROW(mocker.MockFunction(NoReturnType), FunctionMockerException);
    }

}