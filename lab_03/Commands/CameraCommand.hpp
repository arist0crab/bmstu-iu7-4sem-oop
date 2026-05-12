#pragma once

#include "BaseCommand.hpp"
#include "ManagerSolution.hpp"
#include "CameraManager.hpp"
#include "SceneManager.hpp"
#include "TransformManager.hpp"
#include "DefaultCamera.hpp"

class CameraCommand : public BaseCommand
{
	public:
		CameraCommand() = default;
		virtual ~CameraCommand() override = default;
};

class AddCameraCommand : public CameraCommand
{
	public:
		AddCameraCommand() = default;
		virtual ~AddCameraCommand() override = default;

		void execute() override
		{
			auto cameraManager = ManagerSolution::getManager<CameraManager>();
			auto camera = std::make_shared<DefaultCamera>(
				Vertex(0, 0, 100),
				Vertex(0, 0, 0)
			);
			size_t id = cameraManager->addCamera(camera);
			cameraManager->setActiveCamera(id);
		}
};

class RemoveCameraCommand : public CameraCommand
{
	public:
		RemoveCameraCommand(size_t id) : m_id(id) {}
		virtual ~RemoveCameraCommand() override = default;

		void execute() override
		{
			auto cameraManager = ManagerSolution::getManager<CameraManager>();
			cameraManager->removeCamera(m_id);
		}

	private:
		size_t m_id;
};

class SetActiveCameraCommand : public CameraCommand
{
	public:
		SetActiveCameraCommand(size_t id) : m_id(id) {}
		virtual ~SetActiveCameraCommand() override = default;

		void execute() override
		{
			auto cameraManager = ManagerSolution::getManager<CameraManager>();
			cameraManager->setActiveCamera(m_id);
		}

	private:
		size_t m_id;
};

class MoveCameraCommand : public CameraCommand
{
	public:
		MoveCameraCommand(size_t id, double dx, double dy, double dz)
			: m_id(id), m_dx(dx), m_dy(dy), m_dz(dz) {}
		virtual ~MoveCameraCommand() override = default;

		void execute() override
		{
			auto cameraManager = ManagerSolution::getManager<CameraManager>();
			auto camera = cameraManager->getActiveCamera();
			if (camera)
			{
				auto transform = Transform::translation(m_dx, m_dy, m_dz);
				camera->transform(transform);
			}
		}

	private:
		size_t m_id;
		double m_dx, m_dy, m_dz;
};

class RotateCameraCommand : public CameraCommand
{
	public:
		RotateCameraCommand(size_t id, double ax, double ay, double az)
			: m_id(id), m_ax(ax), m_ay(ay), m_az(az) {}
		virtual ~RotateCameraCommand() override = default;

		void execute() override
		{
			auto cameraManager = ManagerSolution::getManager<CameraManager>();
			auto camera = cameraManager->getActiveCamera();
			if (camera)
			{
				auto transform = Transform::rotate(m_ax, m_ay, m_az);
				camera->transform(transform);
			}
		}

	private:
		size_t m_id;
		double m_ax, m_ay, m_az;
};