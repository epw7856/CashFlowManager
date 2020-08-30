#ifndef ERRORCODE_H
#define ERRORCODE_H

enum class ErrorCode
{
    Unknown,                     // Unknown exception
    UnableToSaveConfig,          // Unable to save config file when the application exists
    UnableToCreateNewConfig,     // Unable to create new config file during application startup
    UnableToLoadConfig           // Unable to load existing config file during application startup
};

#endif // ERRORCODE_H
