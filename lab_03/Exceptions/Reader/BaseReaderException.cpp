#include "BaseReaderException.hpp"


BaseReaderException::BaseReaderException(const char *info, const std::source_location &loc) noexcept : BaseException(info, loc) {}