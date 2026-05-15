#pragma once

#include "BaseException.hpp"


class TransformException : public BaseException
{
public:
    TransformException(const char *info, const std::source_location &loc = std::source_location::current()) noexcept;
};

class InvalidScaleException : public TransformException
{
public:
    InvalidScaleException(const char *info = "Invalid scale factor (cannot be zero)", const std::source_location &loc = std::source_location::current()) noexcept;
};

class MatrixSingularException : public TransformException
{
public:
    MatrixSingularException(const char *info = "Matrix is singular or non-invertible", const std::source_location &loc = std::source_location::current()) noexcept;
};