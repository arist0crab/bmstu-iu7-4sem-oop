#pragma once

#include "BaseException.hpp"


class BaseReaderException : public BaseException
{
    public:
        BaseReaderException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};