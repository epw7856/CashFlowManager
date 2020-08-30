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
        case ErrorCode::UnableToSaveConfig:
            return "Unable to save system configuration info!";

        case ErrorCode::UnableToLoadConfig:
            return "Unable to load existing system configuration info!";

        case ErrorCode::UnableToCreateNewConfig:
            return "Unable to create new system configuration file!";

        default:
            return "Unknown exception occurred.";
    }
}
