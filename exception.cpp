#include "exception.h"

CustomException::CustomException(string message) : message("Custom exception: " + message){}
const string& CustomException::getMessage() const noexcept{
    return message;
}