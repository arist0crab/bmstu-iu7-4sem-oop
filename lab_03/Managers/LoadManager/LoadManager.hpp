#pragma once

#include <memory>
#include <string>
#include "BaseObject.hpp"
#include "BaseManager.hpp"
#include "BuilderSolution.hpp"
#include "DirectorSolution.hpp"
#include "ReaderSolution.hpp"
#include "ListBuilder.hpp"
#include "MatrixBuilder.hpp"

class LoadManager : public BaseManager
{
    public:
        LoadManager() = default;
        virtual ~LoadManager() override = default;

        template <typename TBuilder>
        std::shared_ptr<BaseObject> load(const std::string &filename)
        {
            auto reader = ReaderSolution::create(filename);
            auto builder = BuilderSolution::create<TBuilder>();
            auto director = DirectorSolution::create();

            director->setReader(reader);
            director->setBuilder(builder);
            director->build(filename);

            auto model = director->build(filename);
            return model;
        }
};