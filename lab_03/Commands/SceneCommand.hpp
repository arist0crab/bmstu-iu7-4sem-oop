#pragma once

#include "BaseCommand.hpp"
#include "ManagerSolution.hpp"
#include "DrawManager.hpp"
#include "DrawCarcassVisitor.hpp"


class SceneCommand : public BaseCommand
{
    public:
        SceneCommand() = default;
        virtual ~SceneCommand() override = default;
};

class InitSceneCommand : public SceneCommand
{
	public:
		InitSceneCommand() = default;
		virtual ~InitSceneCommand() override = default;

		void execute() override
		{
			auto cameraManager = ManagerSolution::getManager<CameraManager>();
			auto defaultCamera = std::make_shared<DefaultCamera>(
				Vertex(0, 0, 100),
				Vertex(0, 0, 0)
			);
			size_t camId = cameraManager->addCamera(defaultCamera);
			cameraManager->setActiveCamera(camId);
		}
};

class DrawSceneCommand : public SceneCommand
{
    public:
        DrawSceneCommand() = default;
        virtual ~DrawSceneCommand() override = default;

        void execute() override
        {
            auto drawManager = ManagerSolution::getManager<DrawManager>();
            auto visitor = std::make_shared<DrawCarcassVisitor>();
            drawManager->draw(visitor);
        }
};

class ClearSceneCommand : public SceneCommand
{
    public:
        ClearSceneCommand() = default;
        virtual ~ClearSceneCommand() override = default;

        void execute() override
        {
            auto sceneManager = ManagerSolution::getManager<SceneManager>();
            sceneManager->clear();
        }
};