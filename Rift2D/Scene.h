#pragma once
#include <memory>
#include <string>
#include <vector>

namespace rift2d
{
	class RiftActor;
	class Scene
	{
	public:
		RiftActor* addRiftActor(std::unique_ptr<RiftActor> object);
		void removeRiftActor(RiftActor* actor);

		bool isInitialized() const { return m_isInitialized; }

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void rootInit();
		void rootUpdate();
		void rootLateUpdate();
		void rootEnd();
		void rootOnImGui();
		void rootFrameCleanup();

	protected:
		explicit Scene(std::string name);

		virtual void init() = 0;
		virtual void update() {}
		virtual void lateUpdate() {}
		virtual void end() {}
		virtual void onImGui() {}
	private:
		std::string m_name;
		std::vector<std::unique_ptr<RiftActor>> m_rootActors{};
		bool m_isInitialized{ false };
		static unsigned int m_idCounter; 
		void processRiftActorRemovals();

	};

}
