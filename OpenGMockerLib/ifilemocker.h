
#ifndef IFILEMOCKER_H
#define IFILEMOCKER_H

#include "mockerexception.h"

#include <string>

namespace OpenGMocker
{
    MOCKER_EXCEPTION(FileMockerException)

    class IFileMocker
    {
    public:
        virtual ~IFileMocker() = default;
    };
}

#endif // IFILEMOCKER_H
