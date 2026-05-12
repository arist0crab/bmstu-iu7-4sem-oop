#pragma once

#include "BaseCommand.hpp"
#include "BaseObject.hpp"
#include "ManagerSolution.hpp"
#include "SceneManager.hpp"
#include "TransformManager.hpp"


class ObjectCommand : public BaseCommand
{
    public:
        ObjectCommand() = default;
        virtual ~ObjectCommand() override = default;
};

class AddObjectCommand : public ObjectCommand
{
    public:
        AddObjectCommand(std::shared_ptr<BaseObject> object) : m_object(object) { }
        virtual ~AddObjectCommand() override = default;

        void execute() override
        {
            auto sceneManager = ManagerSolution::getManager<SceneManager>();
            sceneManager->addObject(m_object);
        }

    private:
        std::shared_ptr<BaseObject> m_object;
};

class RemoveObjectCommand : public ObjectCommand 
{
    public:
        RemoveObjectCommand(size_t id) : m_id(id) {}
        virtual ~RemoveObjectCommand() override = default;

        void execute() override
        {
            auto sceneManager = ManagerSolution::getManager<SceneManager>();
            sceneManager->removeObject(m_id);
        }

    private:
        size_t m_id;
};

class MoveObjectCommand : public ObjectCommand 
{
    public:
        MoveObjectCommand(size_t id, double dx, double dy, double dz) : m_id(id), m_dx(dx), m_dy(dy), m_dz(dz) {}
        virtual ~MoveObjectCommand() override = default;

        void execute() override
        {
            auto transformManager = ManagerSolution::getManager<TransformManager>();
            transformManager->moveObject(m_id, m_dx, m_dy, m_dz);
        }

    private:
        size_t m_id;
        double m_dx, m_dy, m_dz;
};

class RotateObjectCommand : public ObjectCommand 
{
    public:
        RotateObjectCommand(size_t id, double ax, double ay, double az) : m_id(id), m_angleX(ax), m_angleY(ay), m_angleZ(az) {}
        virtual ~RotateObjectCommand() override = default;

        void execute() override
        {
            auto transformManager = ManagerSolution::getManager<TransformManager>();
            transformManager->rotateObject(m_id, m_angleX, m_angleY, m_angleZ);
        }

    private:
        size_t m_id;
        double m_angleX, m_angleY, m_angleZ;
};

class ScaleObjectCommand : public ObjectCommand 
{
    public:
        ScaleObjectCommand(size_t id, double kx, double ky, double kz) : m_id(id), m_kx(kx), m_ky(ky), m_kz(kz) {}
        virtual ~ScaleObjectCommand() override = default;

        void execute() override
        {
            auto transformManager = ManagerSolution::getManager<TransformManager>();
            transformManager->scaleObject(m_id, m_kx, m_ky, m_kz);
        }

    private:
        size_t m_id;
        double m_kx, m_ky, m_kz;
};

class SurfaceObjectCommand : public ObjectCommand 
{
    public:
        SurfaceObjectCommand() = default;
        virtual ~SurfaceObjectCommand() override = default;

        void execute() override
        {
            // TODO
            // auto sceneManager = ManagerSolution::getManager<SceneManager>();
            // sceneManager->toSurface();
        }
};