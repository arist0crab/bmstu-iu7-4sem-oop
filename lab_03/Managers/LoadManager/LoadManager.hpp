#pragma once

#include <memory>
#include <string>
#include "BuilderSolution.hpp"
#include "BaseManager.hpp"
#include "DirectorSolution.hpp"
#include "ReaderSolution.hpp"
#include "ListBuilder.hpp"
#include "MatrixBuilder.hpp"
#include "SceneManager.hpp"
#include "ManagerSolution.hpp"


class LoadManager : public BaseManager
{
    public:
        LoadManager() = default;
        virtual ~LoadManager() override = default;

        void loadMatrixModel(const std::string &filename)
        {
            load<MatrixBuilder>(filename);
        }

        void loadListModel(const std::string &filename)
        {
            load<ListBuilder>(filename);
        }

        template <typename TBuilder>
        void load(const std::string &filename)
        {
            auto reader = ReaderSolution::create(filename);
            auto builder = BuilderSolution::create<TBuilder>();
            auto director = DirectorSolution::create();

            director->setReader(reader);
            director->setBuilder(builder);

            auto model = director->build(filename);
            
            auto sceneManager = ManagerSolution::getManager<SceneManager>();
            sceneManager->addObject(model);
        }
};