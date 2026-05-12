#pragma once

#include <memory>
#include <string>
#include "BaseObject.hpp"
#include "BaseBuilder.hpp"
#include "BaseReader.hpp"


class Director
{
    public:
        Director() = default;
        ~Director() = default;

        void setBuilder(std::shared_ptr<BaseBuilder> builder);
        void setReader(std::shared_ptr<BaseReader> reader);

        std::shared_ptr<BaseObject> build(const std::string &filename);

    private:
        std::shared_ptr<BaseBuilder> m_builder;
        std::shared_ptr<BaseReader> m_reader;
};