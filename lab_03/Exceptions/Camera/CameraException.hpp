#pragma once

#include "BaseException.hpp"


class CameraException : public BaseException
{
    public:
        CameraException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class CameraNotFoundException : public CameraException
{
    public:
        CameraNotFoundException(const char *info = "Camera not found", const std::source_location &loc = std::source_location::current()) noexcept;
};

class CameraInvalidOperationException : public CameraException
{
    public:
        CameraInvalidOperationException(const char *info = "Invalid camera operation", const std::source_location &loc = std::source_location::current()) noexcept;
};