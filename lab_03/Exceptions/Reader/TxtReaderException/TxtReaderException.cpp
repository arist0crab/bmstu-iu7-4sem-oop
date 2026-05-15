#include "TxtReaderException.hpp"


TxtReaderException::TxtReaderException(const char *info, const std::source_location &loc) noexcept : BaseReaderException(info, loc) {}

TxtReaderFileNotFoundException::TxtReaderFileNotFoundException(const char *info, const std::source_location &loc) noexcept : TxtReaderException(info, loc) {}

TxtReaderParseException::TxtReaderParseException(const char *info, const std::source_location &loc) noexcept : TxtReaderException(info, loc) {}