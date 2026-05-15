#include "SceneException.hpp"


SceneException::SceneException(const char *info, const std::source_location &loc) noexcept : BaseException(info, loc) {}

SceneObjectNotFoundException::SceneObjectNotFoundException(const char *info, const std::source_location &loc) noexcept : SceneException(info, loc) {}

SceneEmptyException::SceneEmptyException(const char *info, const std::source_location &loc) noexcept : SceneException(info, loc) {}

SceneInvalidOperationException::SceneInvalidOperationException(const char *info, const std::source_location &loc) noexcept : SceneException(info, loc) {}