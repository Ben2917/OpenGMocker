
#ifndef OPENGMOCKER_H
#define OPENGMOCKER_H

#include "IOpenGMocker.h"

#include <string>

class OpenGMocker : public IOpenGMocker
{
public:
    OpenGMocker();
    ~OpenGMocker() override;

    std::string MockFunction(const std::string& function);

};

#endif // OPENGMOCKER_H