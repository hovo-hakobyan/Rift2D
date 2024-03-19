#include "RiftActor.h"
#include "GameObject.h"

rift2d::RiftActor::RiftActor(Scene* pScene):
m_pScene{pScene}
{
	m_pRootObject = std::make_unique<GameObject>(this);
}
rift2d::RiftActor::~RiftActor() = default;

rift2d::GameObject* rift2d::RiftActor::registerGameObject(std::unique_ptr<GameObject> obj)
{
	if (!obj)
	{
		return nullptr;
	}

	const auto rawPtr = obj.get();
	m_TempObjects.push_back(std::move(obj));
	return rawPtr;
}

std::unique_ptr<rift2d::GameObject> rift2d::RiftActor::releaseGameObject(GameObject* go)
{
	auto it = std::find_if(m_TempObjects.begin(), m_TempObjects.end(), [go](const auto& rootgo)
		{
			return rootgo.get() == go;
		});
		
	std::unique_ptr<GameObject> child;
	if (it != m_TempObjects.end())
	{
		child = std::move(*it);
		m_TempObjects.erase(it);
	}
		
	return child;
}

void rift2d::RiftActor::init()
{
	m_pRootObject->init();
}

void rift2d::RiftActor::update()
{
	m_pRootObject->update();
}

void rift2d::RiftActor::lateUpdate()
{
	m_pRootObject->lateUpdate();
}

void rift2d::RiftActor::end()
{
	m_pRootObject->end();
}

void rift2d::RiftActor::onImGui()
{
	m_pRootObject->onImGui();
}

void rift2d::RiftActor::markForDestroy()
{
	m_isMarkedForDestruction = true;
	m_pRootObject->markForDestroy();
}

void rift2d::RiftActor::processComponentRemovals()
{
	m_pRootObject->processComponentRemovals();
}

void rift2d::RiftActor::processGameObjectRemovals()
{
	m_pRootObject->processGameObjectRemovals();
}
