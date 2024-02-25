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
#include "SpriteComponent.h"
#include "GameObject.h"

#include <filesystem>
namespace fs = std::filesystem;

void load()
{
	auto& scene = rift2d::SceneManager::GetInstance().CreateScene("Demo");

	auto bg = std::make_shared<rift2d::GameObject>();
	auto spriteComponent = bg->AddComponent<rift2d::SpriteComponent>();
	spriteComponent->SetTexture("background.tga");
	scene.Add(bg);

	auto font = rift2d::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto title = std::make_shared<rift2d::GameObject>();
	auto to =title->AddComponent<rift2d::TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(title);

	auto logo = std::make_shared<rift2d::GameObject>();
	spriteComponent = logo->AddComponent<rift2d::SpriteComponent>();
	spriteComponent->SetTexture("logo.tga");
	spriteComponent->SetPosition(216, 180);
	scene.Add(logo);

	//logo->RemoveComponent<rift2d::TextComponent>();
	//logo->RemoveComponent<rift2d::SpriteComponent>();
	logo->RemoveComponent(spriteComponent);


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
