#pragma once
#include <memory>
#include <vector>

namespace rift2d
{
	class Scene;
	class GameObject;
	class RiftActor
	{
	public:
		RiftActor(Scene* pScene);
		virtual ~RiftActor();
		RiftActor(const RiftActor& other) = delete;
		RiftActor(RiftActor&& other) = delete;
		RiftActor& operator=(const RiftActor& other) = delete;
		RiftActor& operator=(RiftActor&& other) = delete;

		/// <summary>
/// Registers a game object. Without this call you cannot add a gameobject to the scenegraph
/// </summary>
/// <remarks>
/// You should attach this gameobject to the root by calling getRoot(), otherwise it will not get processed.
/// </remarks>
/// <returns>A pointer to the registered gameobject.</returns>
		GameObject* registerGameObject(std::unique_ptr<GameObject> obj);
		std::unique_ptr<GameObject> releaseGameObject(GameObject* go);

		virtual void init();
		virtual void update();
		virtual void lateUpdate();
		virtual void end();
		virtual void onImGui();

		void markForDestroy();
		void processComponentRemovals();
		void processGameObjectRemovals();

		bool isMarkedForDestruction() const { return m_isMarkedForDestruction; }

	protected:
		GameObject* getRoot() const { return m_pRootObject.get(); }
		Scene* getScene() const { return m_pScene; }
 
	private:
		std::unique_ptr<GameObject> m_pRootObject;
		std::vector<std::unique_ptr<GameObject>> m_TempObjects;
		bool m_isMarkedForDestruction{false};
		Scene* m_pScene;
	};

}
