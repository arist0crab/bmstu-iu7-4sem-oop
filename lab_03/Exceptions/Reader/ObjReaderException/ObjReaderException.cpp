#include "ObjReaderException.hpp"


ObjReaderException::ObjReaderException(const char *info, const std::source_location &loc) noexcept : BaseReaderException(info, loc) {}

ObjReaderFileNotFoundException::ObjReaderFileNotFoundException(const char *info, const std::source_location &loc) noexcept : ObjReaderException(info, loc) {}

ObjReaderParseException::ObjReaderParseException(const char *info, const std::source_location &loc) noexcept : ObjReaderException(info, loc) {}