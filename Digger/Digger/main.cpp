#include <Rift2DEngine.h>

#include "InputManager.h"
#include "Scenes/MenuScene.h"
#include "SceneManager.h"
#include "Commands/ToMainMenuCommand.h"
#include "Scenes/GameScene.h"
#include "Scenes/WorldBuilderScene.h"
namespace fs = std::filesystem;

void load()
{
	auto& sceneManager = rift2d::SceneManager::GetInstance();
	sceneManager.addScene(std::make_unique<digger::MenuScene>());

	rift2d::InputManager::GetInstance().bindAction(SDL_SCANCODE_ESCAPE, rift2d::InputEvent::Down, std::make_unique<digger::ToMainMenuCommand>());
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