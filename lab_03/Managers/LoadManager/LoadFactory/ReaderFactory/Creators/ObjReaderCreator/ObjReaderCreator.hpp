#pragma once

#include <memory>
#include "BaseReaderCreator.hpp"
#include "ObjReader.hpp"


class ObjReaderCreator : public BaseReaderCreator
{
    public:
        ObjReaderCreator() = default;
        virtual ~ObjReaderCreator() override = default;

        std::shared_ptr<BaseReader> createReader() override;
};