#include "WorldBuilderScene.h"

#include "Exception.h"
#include "WorldBuilder.h"
#include "Prefabs/DiggerPrefab.h"
#include "Prefabs/EnemyPrefab.h"

digger::WorldBuilderScene::WorldBuilderScene():
Scene("WorldBuilderScene")
{
}

void digger::WorldBuilderScene::init()
{
	auto worldBuilderObj = createGameObject();
	auto comp = worldBuilderObj->addComponent<rift2d::WorldBuilder>(rift2d::TileInfo{ 64,64 }, static_cast<uint8_t>(2));
	comp->addLayerInfo(rift2d::LayerInfo{ 1,rift2d::RiftColor::Brown, "Dirt" });
	comp->addLayerInfo(rift2d::LayerInfo{ 2,rift2d::RiftColor::Green,"Gold" });
	comp->addLayerInfo(rift2d::LayerInfo{ 3,rift2d::RiftColor::Yellow,"Emerald" });
	comp->setWorldPadding(0.f, 20.f);
}
