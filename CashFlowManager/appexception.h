#ifndef APPEXCEPTION_H
#define APPEXCEPTION_H

#include "errorcode.h"
#include <exception>
#include <string>

class AppException : public std::exception
{
public:
    AppException(ErrorCode localCode);
    const char* what() const noexcept override;
    ~AppException() noexcept override {}

private:
    ErrorCode code = ErrorCode::Unknown;
};

#endif // APPEXCEPTION_H
