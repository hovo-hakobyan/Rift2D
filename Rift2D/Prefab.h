#pragma once

namespace rift2d
{
	class GameObject;
	class Scene;
	class Prefab
	{
	public:

		Prefab();
		virtual ~Prefab();
		Prefab(const Prefab& other) = delete;
		Prefab(Prefab&& other) = delete;
		Prefab& operator=(const Prefab& other) = delete;
		Prefab& operator=(Prefab&& other) = delete;

		virtual void setup(GameObject* rootObj, Scene* pScene) = 0;
	};

}
