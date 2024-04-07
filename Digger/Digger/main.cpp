#include <Rift2DEngine.h>
#include "Scenes/MenuScene.h"
#include "SceneManager.h"
#include "Scenes/GameScene.h"
#include "Scenes/WorldBuilderScene.h"
namespace fs = std::filesystem;

void load()
{
	auto& sceneManager = rift2d::SceneManager::GetInstance();

	sceneManager.addScene(std::make_unique<digger::MenuScene>());
	sceneManager.addScene(std::make_unique<digger::WorldBuilderScene>());
	sceneManager.addScene(std::make_unique<digger::GameScene>());

}


int main()
{
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
	rift2d::Rift2DEngine engine(data_location);
	engine.run(load);
	return 0;
}