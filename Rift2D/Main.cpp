#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Rift2DEngine.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Scene.h"
#include "Font.h"
#include "SpriteRenderer.h"

#include <filesystem>
namespace fs = std::filesystem;

void load()
{
	auto& scene = rift2d::SceneManager::GetInstance().CreateScene("Demo");

	auto font = rift2d::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto go = std::make_shared<rift2d::GameObject>();
	auto to =go->AddComponent<rift2d::TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(go);

	//auto sr = std::make_shared<rift2d::SpriteRenderer>();

	/*auto go = std::make_shared<rift2d::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<rift2d::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = rift2d::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<rift2d::TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);*/
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
	engine.Run(load);
    return 0;
}
