#include "ObjectCommand.hpp"
#include "SceneManager.hpp"
#include "TransformManager.hpp"


AddObjectCommand::AddObjectCommand(std::shared_ptr<BaseObject> object) : m_action(&SceneManager::addObject), m_object(object) {}

void AddObjectCommand::execute()
{
	((*m_sceneManager).*m_action)(m_object);
}

RemoveObjectCommand::RemoveObjectCommand(size_t id) : m_action(&SceneManager::removeObject), m_id(id) {}

void RemoveObjectCommand::execute()
{
	((*m_sceneManager).*m_action)(m_id);
}

MoveObjectCommand::MoveObjectCommand(size_t id, double dx, double dy, double dz) : m_action(&TransformManager::moveObject), m_id(id), m_dx(dx), m_dy(dy), m_dz(dz) {}

void MoveObjectCommand::execute()
{
	((*m_transformManager).*m_action)(m_id, m_dx, m_dy, m_dz);
}

RotateObjectCommand::RotateObjectCommand(size_t id, double ax, double ay, double az) : m_action(&TransformManager::rotateObject), m_id(id), m_ax(ax), m_ay(ay), m_az(az) {}

void RotateObjectCommand::execute()
{
	((*m_transformManager).*m_action)(m_id, m_ax, m_ay, m_az);
}

ScaleObjectCommand::ScaleObjectCommand(size_t id, double kx, double ky, double kz) : m_action(&TransformManager::scaleObject), m_id(id), m_kx(kx), m_ky(ky), m_kz(kz) {}

void ScaleObjectCommand::execute()
{
	((*m_transformManager).*m_action)(m_id, m_kx, m_ky, m_kz);
}

SetCenterCommand::SetCenterCommand(size_t id, const Vertex &center) : m_action(&SceneManager::setCenter), m_id(id), m_center(center) {}

void SetCenterCommand::execute()
{
	((*m_sceneManager).*m_action)(m_id, m_center);
}

SurfaceObjectCommand::SurfaceObjectCommand(size_t id) : m_action(&SceneManager::toSurface), m_id(id) {}

void SurfaceObjectCommand::execute()
{
	((*m_sceneManager).*m_action)(m_id);
}