#include "WorldBuilderScene.h"

#include "WorldBuilder.h"

digger::WorldBuilderScene::WorldBuilderScene():
Scene("WorldBuilderScene")
{
}

void digger::WorldBuilderScene::init()
{
	auto worldBuilderObj = createGameObject();
	auto comp = worldBuilderObj->addComponent<rift2d::WorldBuilder>(rift2d::TileInfo{ 64,64 });
	comp->addTileData(rift2d::TileData{ "dirt",rift2d::RiftColor::Orange });
	comp->addTileData(rift2d::TileData{ "enemySpawn",rift2d::RiftColor::Magenta });

}
