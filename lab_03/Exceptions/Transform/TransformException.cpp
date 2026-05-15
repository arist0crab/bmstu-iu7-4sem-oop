#include "TransformException.hpp"

TransformException::TransformException(const char *info, const std::source_location &loc) noexcept  : BaseException(info, loc) {}

InvalidScaleException::InvalidScaleException(const char *info, const std::source_location &loc) noexcept  : TransformException(info, loc) {}

MatrixSingularException::MatrixSingularException(const char *info, const std::source_location &loc) noexcept  : TransformException(info, loc) {}