
#include "utilities.h"

namespace OpenGMocker
{
    std::string ToUpper(std::string str)
    {
        std::ranges::for_each(
            str,
            [](char& c)
            {
                c = std::toupper(c);
            });
        return str;
    }

    std::string ToLower(std::string str)
    {
        std::ranges::for_each(
            str,
            [](char& c)
            {
                c = std::tolower(c);
            });
        return str;
    }
}
