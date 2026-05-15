#include "CameraException.hpp"


CameraException::CameraException(const char *info, const std::source_location &loc) noexcept : BaseException(info, loc) {}

CameraNotFoundException::CameraNotFoundException(const char *info, const std::source_location &loc) noexcept : CameraException(info, loc) {}

CameraInvalidOperationException::CameraInvalidOperationException(const char *info, const std::source_location &loc) noexcept : CameraException(info, loc) {}