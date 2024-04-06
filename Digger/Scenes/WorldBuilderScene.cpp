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
	auto comp = worldBuilderObj->addComponent<rift2d::WorldBuilder>(rift2d::TileInfo{ 64,64 });
	comp->addTileData(rift2d::TileData{ 1,rift2d::RiftColor::Magenta, "player" });
	comp->addTileData(rift2d::TileData{ 2,rift2d::RiftColor::Orange,"enemy" });

}
