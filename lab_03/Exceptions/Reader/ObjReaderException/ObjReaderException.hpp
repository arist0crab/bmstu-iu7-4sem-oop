#pragma once

#include "BaseReaderException.hpp"


class ObjReaderException : public BaseReaderException
{
    public:
        ObjReaderException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class ObjReaderFileNotFoundException : public ObjReaderException
{
    public:
        ObjReaderFileNotFoundException(const char *info = "OBJ file not found", const std::source_location &loc = std::source_location::current()) noexcept;
};

class ObjReaderParseException : public ObjReaderException
{
    public:
        ObjReaderParseException(const char *info = "OBJ parse error", const std::source_location &loc = std::source_location::current()) noexcept;
};