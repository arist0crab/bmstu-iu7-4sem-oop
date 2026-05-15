#pragma once

#include "BaseCommand.hpp"
#include "BaseObject.hpp"
#include "Vertex.hpp"


class ObjectCommand : public BaseCommand
{
    public:
        ObjectCommand() = default;
        virtual ~ObjectCommand() override = default;
};

class AddObjectCommand : public ObjectCommand
{
    public:
        AddObjectCommand(std::shared_ptr<BaseObject> object);
        virtual ~AddObjectCommand() override = default;

        void execute() override;

    private:
        using Action = void (SceneManager::*)(std::shared_ptr<BaseObject>);
        Action m_action;
        std::shared_ptr<BaseObject> m_object;
};

class RemoveObjectCommand : public ObjectCommand
{
    public:
        RemoveObjectCommand(size_t id);
        virtual ~RemoveObjectCommand() override = default;

        void execute() override;

    private:
        using Action = void (SceneManager::*)(size_t);
        Action m_action;
        size_t m_id;
};

class MoveObjectCommand : public ObjectCommand
{
    public:
        MoveObjectCommand(size_t id, double dx, double dy, double dz);
        virtual ~MoveObjectCommand() override = default;

        void execute() override;

    private:
        using Action = void (TransformManager::*)(size_t, double, double, double);
        Action m_action;
        size_t m_id;
        double m_dx, m_dy, m_dz;
};

class RotateObjectCommand : public ObjectCommand
{
    public:
        RotateObjectCommand(size_t id, double ax, double ay, double az);
        virtual ~RotateObjectCommand() override = default;

        void execute() override;

    private:
        using Action = void (TransformManager::*)(size_t, double, double, double);
        Action m_action;
        size_t m_id;
        double m_ax, m_ay, m_az;
};

class ScaleObjectCommand : public ObjectCommand
{
    public:
        ScaleObjectCommand(size_t id, double kx, double ky, double kz);
        virtual ~ScaleObjectCommand() override = default;

        void execute() override;

    private:
        using Action = void (TransformManager::*)(size_t, double, double, double);
        Action m_action;
        size_t m_id;
        double m_kx, m_ky, m_kz;
};

class SetCenterCommand : public ObjectCommand
{
    public:
        SetCenterCommand(size_t id, const Vertex &center);
        virtual ~SetCenterCommand() override = default;

        void execute() override;

    private:
        using Action = void (SceneManager::*)(size_t, const Vertex &);
        Action m_action;
        size_t m_id;
        Vertex m_center;
};

class SurfaceObjectCommand : public ObjectCommand
{
    public:
        SurfaceObjectCommand(size_t id);
        virtual ~SurfaceObjectCommand() override = default;

        void execute() override;

    private:
        using Action = void (SceneManager::*)(size_t);
        Action m_action;
        size_t m_id;
};