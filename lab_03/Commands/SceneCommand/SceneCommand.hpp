#pragma once

#include "BaseCommand.hpp"
#include "DrawVisitor.hpp"


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
        using AddAction = size_t (CameraManager::*)();
        using SetAction = void (CameraManager::*)(size_t);
        AddAction m_addAction;
        SetAction m_setAction;
};

class DrawSceneCommand : public SceneCommand
{
    public:
        DrawSceneCommand();
        virtual ~DrawSceneCommand() override = default;

        void execute() override;

    private:
        using Action = void (DrawManager::*)(std::shared_ptr<DrawVisitor>);
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