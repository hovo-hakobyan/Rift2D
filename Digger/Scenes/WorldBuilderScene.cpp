#include "WorldBuilderScene.h"

#include "Exception.h"
#include "WorldBuilder.h"

digger::WorldBuilderScene::WorldBuilderScene():
Scene("WorldBuilderScene")
{
}

void digger::WorldBuilderScene::init()
{
	auto worldBuilderObj = createGameObject();
	auto comp = worldBuilderObj->addComponent<rift2d::WorldBuilder>(rift2d::TileInfo{ 64,64 });
	comp->addTileData(rift2d::TileData{ 1,rift2d::RiftColor::Orange,"dirt" });
	comp->addTileData(rift2d::TileData{ 2,rift2d::RiftColor::Magenta, "something" });

	try
	{
		rift2d::WorldBuilder::buildLevel("level0");
	}
	catch (const rift2d::RiftException& e )
	{
		e.logToFile();
		throw;
	}
	

}
