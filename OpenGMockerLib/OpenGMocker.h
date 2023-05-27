
#ifndef OPENGMOCKER_H
#define OPENGMOCKER_H

#include "IOpenGMocker.h"

#include <string>
#include <vector>

class OpenGMocker : public IOpenGMocker
{
public:
    OpenGMocker();
    ~OpenGMocker() override;

    std::string MockFunction(const std::string& function_);

private:
    template <typename ValueType>
    using ValueOffset = std::pair<ValueType, size_t>;

    struct Param
    {
        std::string type;
        std::string name;
    };

    size_t GetVirtualEnd();
    ValueOffset<std::string> GetReturnType();
    ValueOffset<std::string> GetFunctionName();
    ValueOffset<std::vector<Param>> GetParams();
    bool IsConstQualified() const;

    std::string function;

};

#endif // OPENGMOCKER_H