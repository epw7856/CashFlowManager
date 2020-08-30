#include "appexception.h"

AppException::AppException(ErrorCode localCode)
:
    code(localCode)
{

}

const char* AppException::what() const noexcept
{
    switch(code)
    {


        default:
            return "Unknown exception occurred.";
    }
}
