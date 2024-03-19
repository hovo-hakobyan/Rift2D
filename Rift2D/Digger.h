#pragma once
#include "RiftActor.h"

namespace rift2d
{
	class Scene;

	class Digger :public RiftActor
	{
	public:

		Digger(rift2d::Scene* pScene);
		virtual ~Digger() override;
		Digger(const Digger& other) = delete;
		Digger(Digger&& other) = delete;
		Digger& operator=(const Digger& other) = delete;
		Digger& operator=(Digger&& other) = delete;

		virtual void init() override;
		virtual void update() override;
		virtual void end() override;
	};


}
