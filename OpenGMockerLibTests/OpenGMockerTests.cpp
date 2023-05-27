
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

TEST_F(OpenGMockerTests, GenerateMockFromFunctionPrimitiveReturnNoParamsNoQualifiers)
{
    constexpr auto Function = "virtual int TestFunction() = 0;";
    constexpr auto ExpectedMock = "MOCK_METHOD(int, TestFunction, (), (override));";
    OpenGMocker mocker;

    std::string actualMock;
    EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

    EXPECT_EQ(ExpectedMock, actualMock);
}

TEST_F(OpenGMockerTests, GenerateMockFromFunctionPrimitiveReturnNoParamsConstQualified)
{
    constexpr auto Function = "virtual int TestFunction() const = 0;";
    constexpr auto ExpectedMock = "MOCK_METHOD(int, TestFunction, (), (const, override));";
    OpenGMocker mocker;

    std::string actualMock;
    EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

    EXPECT_EQ(ExpectedMock, actualMock);
}

TEST_F(OpenGMockerTests, MockFunctionThrowsTryingToMockANonVirtualFunction)
{
    constexpr auto Function = "int TestFunction() = 0;";
    OpenGMocker mocker;

    EXPECT_THROW(mocker.MockFunction(Function), std::exception);
}

TEST_F(OpenGMockerTests, GenerateMockFromFunctionPrimitiveReturnPrimitiveParams)
{
    constexpr auto Function = "virtual int TestFunction(int first, double second, float third) = 0;";
    constexpr auto ExpectedMock = "MOCK_METHOD(int, TestFunction, (int first, double second, float third), (override));";
    OpenGMocker mocker;

    std::string actualMock;
    EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

    EXPECT_EQ(ExpectedMock, actualMock);
}

TEST_F(OpenGMockerTests, GenerateMockFromFunctionNoReturnComplexParams)
{
    constexpr auto Function = "virtual void TestFunction(std::pair<int, int> coords, const std::vector<std::string> &values) = 0;";
    constexpr auto ExpectedMock = "MOCK_METHOD(void, TestFunction, (std::pair<int, int> coords, const std::vector<std::string> &values), (override));";
    OpenGMocker mocker;

    std::string actualMock;
    EXPECT_NO_THROW(actualMock = mocker.MockFunction(Function));

    EXPECT_EQ(ExpectedMock, actualMock);
}