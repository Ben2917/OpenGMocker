
#include "filemocker.h"
#include "classmocker.h"
#include "functionmocker.h"

#include <iostream>

namespace
{
    // Return codes
    constexpr auto OK                   = 0;
    constexpr auto INVALID_ARGS         = 1;
    constexpr auto FILE_MOCKER_ERR      = 2;
    constexpr auto CLASS_MOCKER_ERR     = 3;
    constexpr auto FUNCTION_MOCKER_ERR  = 4;
    constexpr auto UNKNOWN_ERR          = 5;
}

int main(int argc, const char **argv)
{
    if (argc != 3)
    {
        std::cout << "Usage: OpenGMocker.exe <input filename> <output filename>\n";
        return INVALID_ARGS;
    }

    try
    {
        auto functionMocker = std::make_unique<OpenGMocker::FunctionMocker>();
        auto classMocker = std::make_unique<OpenGMocker::ClassMocker>(std::move(functionMocker));

        OpenGMocker::FileMocker::Settings settings;
        auto fileMocker = std::make_unique<OpenGMocker::FileMocker>(std::move(classMocker), settings);

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
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
        return UNKNOWN_ERR;
    }
}