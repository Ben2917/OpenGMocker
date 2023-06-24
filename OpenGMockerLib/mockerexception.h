
#ifndef MOCKEREXCEPTION_H
#define MOCKEREXCEPTION_H

#define MOCKER_EXCEPTION(XMockerException)                  \
    class XMockerException : public std::exception          \
    {                                                       \
    public:                                                 \
        XMockerException(const std::string& msg_) :         \
            msg(msg_)                                       \
        {                                                   \
        }                                                   \
                                                            \
        const char* what() const noexcept override          \
        {                                                   \
            return msg.c_str();                             \
        }                                                   \
                                                            \
    private:                                                \
        std::string msg;                                    \
    };                                                      \


#endif // MOCKEREXCEPTION_H