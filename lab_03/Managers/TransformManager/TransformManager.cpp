#include "TransformManager.hpp"


void TransformManager::moveObject(size_t id, double dx, double dy, double dz)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto object = sceneManager->getObject(id);

	if (object)
	{
		auto transform = Transform::translation(dx, dy, dz);
		object->transform(transform);
	}
}

void TransformManager::scaleObject(size_t id, double kx, double ky, double kz)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto object = sceneManager->getObject(id);
	if (object)
	{
		auto transform = Transform::scale(kx, ky, kz);
		object->transform(transform);
	}
}

void TransformManager::rotateObject(size_t id, double ax, double ay, double az)
{
	auto sceneManager = ManagerSolution::getManager<SceneManager>();
	auto object = sceneManager->getObject(id);
	if (object)
	{
		auto transform = Transform::rotate(ax, ay, az);
		object->transform(transform);
	}
}