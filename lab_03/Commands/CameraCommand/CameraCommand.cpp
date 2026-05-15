#include "CameraCommand.hpp"
#include "CameraManager.hpp"
#include "TransformManager.hpp"


AddDefaultCameraCommand::AddDefaultCameraCommand() : m_action(&CameraManager::addDefaultCamera) {}

void AddDefaultCameraCommand::execute()
{
	((*m_cameraManager).*m_action)();
}

RemoveCameraCommand::RemoveCameraCommand(size_t id) : m_action(&CameraManager::removeCamera), m_id(id) {}

void RemoveCameraCommand::execute()
{
	((*m_cameraManager).*m_action)(m_id);
}

SetActiveCameraCommand::SetActiveCameraCommand(size_t id) : m_action(&CameraManager::setActiveCamera), m_id(id) {}

void SetActiveCameraCommand::execute()
{
	((*m_cameraManager).*m_action)(m_id);
}

MoveCameraCommand::MoveCameraCommand(size_t id, double dx, double dy, double dz) : m_action(&TransformManager::moveObject), m_id(id), m_dx(dx), m_dy(dy), m_dz(dz) {}

void MoveCameraCommand::execute()
{
	((*m_transformManager).*m_action)(m_id, m_dx, m_dy, m_dz);
}

RotateCameraCommand::RotateCameraCommand(size_t id, double ax, double ay, double az) : m_action(&TransformManager::rotateObject), m_id(id), m_ax(ax), m_ay(ay), m_az(az) {}

void RotateCameraCommand::execute()
{
	((*m_transformManager).*m_action)(m_id, m_ax, m_ay, m_az);
}