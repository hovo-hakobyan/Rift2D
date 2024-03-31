
#include <Rift2DEngine.h>
#include "Scenes/MenuScene.h"
#include "SceneManager.h"
namespace fs = std::filesystem;

void load()
{
	rift2d::SceneManager::GetInstance().addScene(std::make_unique<digger::MenuScene>());
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