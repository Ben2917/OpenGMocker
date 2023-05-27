
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