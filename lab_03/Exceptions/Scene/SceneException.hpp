#pragma once

#include "BaseException.hpp"


class SceneException : public BaseException
{
    public:
        SceneException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class SceneObjectNotFoundException : public SceneException
{
    public:
        SceneObjectNotFoundException(const char *info = "Scene object not found", const std::source_location &loc = std::source_location::current()) noexcept;
};

class SceneEmptyException : public SceneException
{
    public:
        SceneEmptyException(const char *info = "Scene is empty", const std::source_location &loc = std::source_location::current()) noexcept;
};

class SceneInvalidOperationException : public SceneException
{
    public:
        SceneInvalidOperationException(const char *info = "Invalid scene operation", const std::source_location &loc = std::source_location::current()) noexcept;
};