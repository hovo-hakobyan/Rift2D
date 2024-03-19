#include "Scene.h"
#include "RiftActor.h"
#include <algorithm>
#include <ranges>

using namespace rift2d;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(std::move(name)) {}

Scene::~Scene() = default;

RiftActor* Scene::addRiftActor(std::unique_ptr<RiftActor> object)
{
	if (!object)
	{
		return nullptr;
	}

	const auto rawPtr = object.get();
	m_rootActors.push_back(std::move(object));
	return rawPtr;
}

void Scene::removeRiftActor(RiftActor* actor)
{
	if (!actor)
	{
		return;
	}
	actor->markForDestroy();
}


void Scene::rootInit()
{
	init();

	for (const auto& object : m_rootActors)
	{
		object->init();
	}
	m_isInitialized = true;
}

void Scene::rootUpdate() 
{
	update();

	for(const auto& object : m_rootActors)
	{
		object->update();
	}

}

void Scene::rootLateUpdate() 
{
	lateUpdate();

	for (const auto& object : m_rootActors)
	{
		object->lateUpdate();
	}
}

void rift2d::Scene::rootEnd()
{
	end();

	for (auto& object : m_rootActors)
	{
		object->end();
	}
}

void Scene::rootOnImGui()
{
	onImGui();

	for (const auto& object : m_rootActors)
	{
		object->onImGui();
	}
}

void Scene::rootFrameCleanup() 
{
	//remove dead riftactors
	processRiftActorRemovals();

	for (const auto& object : m_rootActors)
	{
		object->processComponentRemovals();
	}
}

void Scene::processRiftActorRemovals()
{
	// Filter elements that are marked for destruction and call end
	//Invokes IsMarkedForDestruction for each child and if true, invokes end();
	for (const auto& child : m_rootActors | std::views::filter(&RiftActor::isMarkedForDestruction))
	{
		child->end();
	}

	m_rootActors.erase(std::remove_if(m_rootActors.begin(), m_rootActors.end(),
		[](const std::unique_ptr<RiftActor>& child) { return child->isMarkedForDestruction(); }),
		m_rootActors.end());

	//filter elements that are not marked for destruction
	//Cannot bind function pointer because return is inverted
	for (const auto& child : m_rootActors)
	{
		child->processGameObjectRemovals();
	}

}


