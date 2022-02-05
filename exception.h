#pragma once

#include "helper.h"

class CustomException{
private:
    string message;

public:
    CustomException(string);
    const string& getMessage() const noexcept;
};