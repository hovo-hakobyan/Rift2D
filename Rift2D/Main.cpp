#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif
#include "SceneManager.h"
#include "Rift2DEngine.h"
#include "ResourceManager.h"
#include <filesystem>
#include <iostream>
#include "MenuScene.h"

#pragma warning(push)
#pragma warning(disable: 4996)
#include <steam_api.h>
#pragma warning (pop)

namespace fs = std::filesystem;

void load()
{
	rift2d::SceneManager::GetInstance().addScene(std::make_unique<rift2d::MenuScene>());

}

int main(int, char*[])
{
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif

	if(!SteamAPI_Init())
	{
		std::cerr << "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed)." << std::endl;
		return 1;
	}
	std::cout << "Successfully initialized steam.\n";

	rift2d::Rift2DEngine engine(data_location);
	engine.run(load);

	SteamAPI_Shutdown();
    return 0;
}
