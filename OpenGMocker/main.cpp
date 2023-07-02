
#include "filemocker.h"
#include "classmocker.h"
#include "functionmocker.h"
#include "commandlineconfig.h"

#include <iostream>

namespace
{
    // Return codes
    constexpr auto OK                   = 0;
    constexpr auto INVALID_ARGS         = 1;
    constexpr auto FILE_MOCKER_ERR      = 2;
    constexpr auto CLASS_MOCKER_ERR     = 3;
    constexpr auto FUNCTION_MOCKER_ERR  = 4;
    constexpr auto INVALID_ARG_ERR      = 5;

    constexpr auto UNKNOWN_ERR          = 100;

    constexpr auto CONFIG_ARGS_OFFSET   = 3;

    std::vector<std::string> ArgsIntoVector(const char** args, int argsCount)
    {
        std::vector<std::string> argVector;
        for (int argIndex = CONFIG_ARGS_OFFSET; argIndex < argsCount; argIndex++)
        {
            argVector.push_back(args[argIndex]);
        }
        return argVector;
    }
}

int main(int argc, const char **argv)
{
    if (argc < 3)
    {
        std::cout << "Usage: OpenGMocker.exe <input filename> <output filename>\n";
        return INVALID_ARGS;
    }

    try
    {
        const auto argsVector = ArgsIntoVector(argv, argc);
        auto config = std::make_shared<OpenGMocker::CommandLineConfig>(argsVector);

        auto functionMocker = std::make_unique<OpenGMocker::FunctionMocker>();
        auto classMocker = std::make_unique<OpenGMocker::ClassMocker>(std::move(functionMocker), config);

        auto fileMocker = std::make_unique<OpenGMocker::FileMocker>(std::move(classMocker), config);

        fileMocker->MockFile(argv[1], argv[2]);

        return OK;
    }
    catch (const OpenGMocker::FileMockerException& e)
    {
        std::cout << e.what() << "\n";
        return FILE_MOCKER_ERR;
    }
    catch (const OpenGMocker::ClassMockerException& e)
    {
        std::cout << e.what() << "\n";
        return CLASS_MOCKER_ERR;
    }
    catch (const OpenGMocker::FunctionMockerException& e)
    {
        std::cout << e.what() << "\n";
        return FUNCTION_MOCKER_ERR;
    }
    catch (const std::invalid_argument& e)
    {
        std::cout << e.what() << "\n";
        return INVALID_ARG_ERR;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
        return UNKNOWN_ERR;
    }
}