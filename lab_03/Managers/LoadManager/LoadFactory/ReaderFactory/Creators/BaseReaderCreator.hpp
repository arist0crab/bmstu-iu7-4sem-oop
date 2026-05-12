#pragma once

#include <memory>
#include "BaseReader.hpp"

class BaseReaderCreator
{
    public:
        BaseReaderCreator() = default;
        virtual ~BaseReaderCreator() = default;

        virtual std::shared_ptr<BaseReader> createReader() = 0;
};