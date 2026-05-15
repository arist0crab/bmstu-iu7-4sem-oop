#pragma once

#include "BaseCommand.hpp"
#include "DefaultCamera.hpp"


class CameraCommand : public BaseCommand
{
	public:
		CameraCommand() = default;
		virtual ~CameraCommand() override = default;
};

class AddDefaultCameraCommand : public CameraCommand
{
	public:
		AddDefaultCameraCommand();

		void execute() override;

	private:
		using Action = size_t (CameraManager::*)();
		Action m_action;
};

class RemoveCameraCommand : public CameraCommand
{
	public:
		RemoveCameraCommand(size_t id);
		virtual ~RemoveCameraCommand() override = default;

		void execute() override;

	private:
		using Action = void (CameraManager::*)(size_t);
		Action m_action;
		size_t m_id;
};

class SetActiveCameraCommand : public CameraCommand
{
	public:
		SetActiveCameraCommand(size_t id);
		virtual ~SetActiveCameraCommand() override = default;

		void execute() override;

	private:
		using Action = void (CameraManager::*)(size_t);
		Action m_action;
		size_t m_id;
};

class MoveCameraCommand : public CameraCommand
{
	public:
		MoveCameraCommand(size_t id, double dx, double dy, double dz);
		virtual ~MoveCameraCommand() override = default;

		void execute() override;

	private:
		using Action = void (TransformManager::*)(size_t, double, double, double);
		Action m_action;
		size_t m_id;
		double m_dx, m_dy, m_dz;
};

class RotateCameraCommand : public CameraCommand
{
	public:
		RotateCameraCommand(size_t id, double ax, double ay, double az);
		virtual ~RotateCameraCommand() override = default;

		void execute() override;

	private:
		using Action = void (TransformManager::*)(size_t, double, double, double);
		Action m_action;
		size_t m_id;
		double m_ax, m_ay, m_az;
};