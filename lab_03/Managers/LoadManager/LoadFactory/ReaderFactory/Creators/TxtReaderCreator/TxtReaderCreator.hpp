#pragma once

#include <memory>
#include "BaseReaderCreator.hpp"
#include "TxtReader.hpp"


class TxtReaderCreator : public BaseReaderCreator
{
    public:
        TxtReaderCreator() = default;
        virtual ~TxtReaderCreator() override = default;

        std::shared_ptr<BaseReader> createReader() override;
};