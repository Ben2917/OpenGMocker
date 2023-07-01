
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
        constexpr auto input = R"(class ITestInterface
{
public:
    virtual ~ITestInterface() = default;
};)";

        constexpr auto expectedOutput = R"(class MockITestInterface : public ITestInterface
{
public:
};
)";
        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

    TEST_F(ClassMockerTests, MockInterfaceWithOneFunctionTabIndentation)
    {
        constexpr auto input = R"(class ITestInterface
{
public:
    virtual ~ITestInterface() = default;
    virtual void TestFunction() const = 0;
};)";

        constexpr auto expectedOutput = R"(class MockITestInterface : public ITestInterface
{
public:
    MOCK_METHOD(void, TestFunction, (), (const, override));
};
)";
        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void TestFunction() const = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, TestFunction, (), (const, override));"));

        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

    TEST_F(ClassMockerTests, MockInterfaceWithOneFunctionSpaceIndentation)
    {
        constexpr auto input = R"(class ITestInterface
{
public:
    virtual ~ITestInterface() = default;
    virtual void TestFunction() const = 0;
};)";

        constexpr auto expectedOutput = R"(class MockITestInterface : public ITestInterface
{
public:
    MOCK_METHOD(void, TestFunction, (), (const, override));
};
)";
        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void TestFunction() const = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, TestFunction, (), (const, override));"));

        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

    TEST_F(ClassMockerTests, MockInterfaceWithMoreThanFunctions)
    {
        constexpr auto input = R"(class ITestInterface
{
public:
    // Enumeration to represent possible states
    enum class State
    {
        One,
        Two,
        Three
    };

    virtual ~ITestInterface() = default;
    virtual void TestFunction() const = 0;
"};)";

        constexpr auto expectedOutput = R"(class MockITestInterface : public ITestInterface
{
public:
    MOCK_METHOD(void, TestFunction, (), (const, override));
};
)";

        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void TestFunction() const = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, TestFunction, (), (const, override));"));

        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);
    }

    TEST_F(ClassMockerTests, CanGetClassName)
    {
        constexpr auto input = R"(class ITestInterface
{
public:
    virtual ~ITestInterface() = default;
};)";

        constexpr auto expectedClassName = "ITestInterface";

        ClassMocker mocker(std::move(mockFunctionMocker));

        EXPECT_NO_THROW(mocker.MockClass(input));

        ASSERT_EQ(mocker.GetClassName(), expectedClassName);
    }

    TEST_F(ClassMockerTests, ThrowsOnNoClassName)
    {
        ClassMocker mocker(std::move(mockFunctionMocker));
        EXPECT_THROW(mocker.GetClassName(), ClassMockerException);
    }

    TEST_F(ClassMockerTests, CanHandleBigClassWithFactoryFunctions)
    {
        constexpr auto input = R"(class ITestInterface
{

public:
    virtual ~ITestInterface() = default;

    static std::unique_ptr<ISomeInterface> Create(int i, double j, Item k);
    static std::unique_ptr<ISomeInterface> CreateInADifferentWay(const std::string &z, Item k);

    virtual int Getter() const = 0;
    virtual void Setter(int val) = 0;

    enum class State
    {
        GOOD,
        BAD,
        UGLY
    }

    virtual void Time() = 0;
    virtual void To() = 0;
    virtual void SayGoodbye() = 0;
};)";

        constexpr auto expectedOutput = R"(class MockITestInterface : public ITestInterface
{
public:
    MOCK_METHOD(int, Getter, (), (const, override));
    MOCK_METHOD(void, Setter, (int val), (override));
    MOCK_METHOD(void, Time, (), (override));
    MOCK_METHOD(void, To, (), (override));
    MOCK_METHOD(void, SayGoodbye, (), (override));
};
)";

        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual int Getter() const = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(int, Getter, (), (const, override));"));

        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void Setter(int val) = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, Setter, (int val), (override));"));

        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void Time() = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, Time, (), (override));"));

        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void To() = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, To, (), (override));"));

        EXPECT_CALL(*mockFunctionMocker, MockFunction("virtual void SayGoodbye() = 0;"))
            .Times(1)
            .WillOnce(::testing::Return("MOCK_METHOD(void, SayGoodbye, (), (override));"));

        ClassMocker mocker(std::move(mockFunctionMocker));

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockClass(input));
        ASSERT_EQ(expectedOutput, actualOutput);


    }

}