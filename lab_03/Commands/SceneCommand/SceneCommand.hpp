#pragma once

#include <memory>
#include "BaseCommand.hpp"

class SceneManager;
class DrawManager;

class SceneCommand : public BaseCommand
{
    public:
        SceneCommand() = default;
        virtual ~SceneCommand() override = default;
};

class InitSceneCommand : public SceneCommand
{
    public:
        InitSceneCommand();
        virtual ~InitSceneCommand() override = default;

        void execute() override;

    private:
        using Action = void (SceneManager::*)();
        Action m_action;
};

class DrawSceneCommand : public SceneCommand
{
    public:
        DrawSceneCommand();
        virtual ~DrawSceneCommand() override = default;

        void execute() override;

    private:
        using Action = void (DrawManager::*)();
        Action m_action;
}; 

class ClearSceneCommand : public SceneCommand
{
    public:
        ClearSceneCommand();
        virtual ~ClearSceneCommand() override = default;

        void execute() override;

    private:
        using Action = void (SceneManager::*)();
        Action m_action;
};