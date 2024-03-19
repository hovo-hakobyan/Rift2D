#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Rift2DEngine.h"
#include "ResourceManager.h"
#include <filesystem>
#include "MenuScene.h"
#include "SceneManager.h"

namespace fs = std::filesystem;

void load()
{
	rift2d::SceneManager::GetInstance().addScene(std::make_unique<rift2d::MenuScene>());

}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	rift2d::Rift2DEngine engine(data_location);
	engine.run(load);
    return 0;
}
