#pragma once

#include "BaseReaderException.hpp"


class TxtReaderException : public BaseReaderException
{
    public:
        TxtReaderException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class TxtReaderFileNotFoundException : public TxtReaderException
{
    public:
        TxtReaderFileNotFoundException(const char *info = "TXT file not found", const std::source_location &loc = std::source_location::current()) noexcept;
};

class TxtReaderParseException : public TxtReaderException
{
    public:
        TxtReaderParseException(const char *info = "TXT parse error", const std::source_location &loc = std::source_location::current()) noexcept;
};