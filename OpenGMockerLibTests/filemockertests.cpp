
#include "filemocker.h"

#include "mockclassmocker.h"

#include <format>
#include <gtest/gtest.h>

namespace OpenGMocker
{
    class FileMockerTests : public ::testing::Test
    {
    protected:
        FileMockerTests() :
            mockClassMocker(std::make_unique<MockClassMocker>())
        {
        }

        std::unique_ptr<MockClassMocker> mockClassMocker;
    };

    TEST_F(FileMockerTests, ConstructsWithoutThrowing)
    {
        FileMocker::Settings settings;
        EXPECT_NO_THROW(FileMocker mocker(std::move(mockClassMocker), settings));
    }

    TEST_F(FileMockerTests, MockFileContentWithBasicClassInNamespace)
    {
        constexpr auto classInput = 
            "class ITestClass\n"
            "{\n"
            "\tvirtual ~ITestClass() = default;\n"
            "\n"
            "\tvirtual void TestFunction() = 0;\n"
            "};\n";

        constexpr auto classOutput =
            "class MockITestClass : public ITestClass\n"
            "{\n"
            "\tMOCK_METHOD(void, TestFunction, (), (override));\n"
            "};\n";

        constexpr auto input = 
            "#ifndef TESTCLASS_H\n"
            "#define TESTCLASS_H\n"
            "namespace Test\n"
            "{\n"
            "class ITestClass\n"
            "{\n"
            "\tvirtual ~ITestClass() = default;\n"
            "\n"
            "\tvirtual void TestFunction() = 0;\n"
            "};\n"
            "}\n"
            "#endif // TESTCLASS_H";

        constexpr auto expectedOutput = 
            "#ifndef MOCKITESTCLASS_H\n"
            "#define MOCKITESTCLASS_H\n"
            "\n"
            "#include \"itestclass.h\"\n"
            "#include <gmock/gmock.h>\n"
            "\n"
            "namespace Test\n"
            "{\n"
            "class MockITestClass : public ITestClass\n"
            "{\n"
            "\tMOCK_METHOD(void, TestFunction, (), (override));\n"
            "};\n"
            "}\n"
            "\n"
            "#endif // MOCKITESTCLASS_H";

        EXPECT_CALL(*mockClassMocker, MockClass(classInput))
            .Times(1)
            .WillOnce(::testing::Return(classOutput));
        EXPECT_CALL(*mockClassMocker, GetClassName())
            .Times(1)
            .WillOnce(::testing::Return("ITestClass"));
        FileMocker::Settings settings;
        FileMocker mocker(std::move(mockClassMocker), settings);

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockFileContent(input));
        EXPECT_EQ(expectedOutput, actualOutput);
    }

    TEST_F(FileMockerTests, MockFileContentWithBasicClassNoNamespace)
    {
        constexpr auto classInput =
            "class ITestClass\n"
            "{\n"
            "\tvirtual ~ITestClass() = default;\n"
            "\n"
            "\tvirtual void TestFunction() = 0;\n"
            "};\n";

        constexpr auto classOutput =
            "class MockITestClass : public ITestClass\n"
            "{\n"
            "\tMOCK_METHOD(void, TestFunction, (), (override));\n"
            "};\n";

        constexpr auto input =
            "#ifndef TESTCLASS_H\n"
            "#define TESTCLASS_H\n"
            "\n"
            "class ITestClass\n"
            "{\n"
            "\tvirtual ~ITestClass() = default;\n"
            "\n"
            "\tvirtual void TestFunction() = 0;\n"
            "};\n"
            "\n"
            "#endif // TESTCLASS_H";

        constexpr auto expectedOutput =
            "#ifndef MOCKITESTCLASS_H\n"
            "#define MOCKITESTCLASS_H\n"
            "\n"
            "#include \"itestclass.h\"\n"
            "#include <gmock/gmock.h>\n"
            "\n"
            "class MockITestClass : public ITestClass\n"
            "{\n"
            "\tMOCK_METHOD(void, TestFunction, (), (override));\n"
            "};\n"
            "\n"
            "#endif // MOCKITESTCLASS_H";

        EXPECT_CALL(*mockClassMocker, MockClass(classInput))
            .Times(1)
            .WillOnce(::testing::Return(classOutput));
        EXPECT_CALL(*mockClassMocker, GetClassName())
            .Times(1)
            .WillOnce(::testing::Return("ITestClass"));
        FileMocker::Settings settings;
        FileMocker mocker(std::move(mockClassMocker), settings);

        std::string actualOutput;
        EXPECT_NO_THROW(actualOutput = mocker.MockFileContent(input));
        EXPECT_EQ(expectedOutput, actualOutput);
    }
}