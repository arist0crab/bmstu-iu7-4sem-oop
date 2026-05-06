#pragma once

#define EXCEPTION_MESSAGE_SIZE 512

#include <source_location>
#include <cstdio>
#include <exception>

class BaseException : public std::exception
{
    protected:
        char message[EXCEPTION_MESSAGE_SIZE];

    public:
    
        BaseException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept
        {
            snprintf(
                message, 
                EXCEPTION_MESSAGE_SIZE, 
                "File: %s (%d:%d) `%s`: %s\n", 
                loc.file_name(), 
                loc.line(),
                loc.column(), 
                loc.function_name(), 
                info
            );
        }

        virtual const char *what() const noexcept override
        {
            return message;
        }
};