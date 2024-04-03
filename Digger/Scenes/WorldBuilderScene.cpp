#include "WorldBuilderScene.h"

#include "WorldBuilder.h"

digger::WorldBuilderScene::WorldBuilderScene():
Scene("WorldBuilderScene")
{
}

void digger::WorldBuilderScene::init()
{
	/*auto worldBuilderObj = createGameObject();
	auto comp = worldBuilderObj->addComponent<rift2d::WorldBuilder>(rift2d::TileInfo{ 64,64 },"Level1");
	comp->addTileData(rift2d::TileData{ 0,rift2d::RiftColor::Orange,"First" });
	comp->addTileData(rift2d::TileData{ 1,rift2d::RiftColor::Magenta, "Second" });*/

	rift2d::WorldBuilder::buildLevel("Level1");

}
