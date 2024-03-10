#pragma once
#include "BaseComponent.h"
#include "LineGraph.h"

namespace rift2d
{
	class TrashTheCache final : public BaseComponent, public IComponentWatcher
	{
	public:
		TrashTheCache(GameObject* owner);
		virtual ~TrashTheCache() override = default;
		TrashTheCache(const TrashTheCache& other) = delete;
		TrashTheCache(TrashTheCache&& other) = delete;
		TrashTheCache& operator=(const TrashTheCache& other) = delete;
		TrashTheCache& operator=(TrashTheCache&& other) = delete;

		virtual void init() override;
		virtual void update() override;
		virtual void onImGui() override;
		virtual void end() override;

		virtual void onComponentRemoved(BaseComponent* component) override;

	private:
		LineGraph* m_pLineGraphBasic{};
		LineGraph* m_pLineGraph{};
		LineGraph* m_pLineGraphAlt{};
		LineGraph* m_pLineGraphCombined{};
		bool m_shouldTrashGameObj{};
		bool m_shouldTrashGameObjAlt{};
		bool m_shouldTrashBasic{};
		int m_nrSamples{5};

		struct transform {
			float matrix[16] =
			{
				1,0,0,0,
				0,1,0,0,
				0,0,1,0
				,0,0,0,1
			};
		};

		struct gameObject3D
		{
		public:
			transform local;
			int id;
		};
		struct gameObject3DAlt
		{
		public:
			transform* local;
			int id;
		};

		void TrashTheCacheEx1();
		void TrashTheCacheEx2();
		void TrashTheCacheEx3();
	};
}
