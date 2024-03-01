#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Rift2DEngine.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "Font.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

void load()
{
	auto& scene = rift2d::SceneManager::GetInstance().CreateScene("Demo");

	//Resources
	auto font = rift2d::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto gameObject = std::make_unique<rift2d::GameObject>();
	auto spriteComponent = gameObject->AddComponent<rift2d::SpriteComponent>();
	spriteComponent->SetTexture("background.tga");
	scene.Add(std::move(gameObject));

	
	gameObject = std::make_unique<rift2d::GameObject>();
	auto to = gameObject->AddComponent<rift2d::TextComponent>("Programming 4 Assignment", font);
	to->SetPosition(80, 50);
	scene.Add(std::move(gameObject));

	gameObject = std::make_unique<rift2d::GameObject>();
	spriteComponent = gameObject->AddComponent<rift2d::SpriteComponent>();
	spriteComponent->SetTexture("logo.tga");
	spriteComponent->SetPosition(216, 180);
	scene.Add(std::move(gameObject));

	gameObject = std::make_unique<rift2d::GameObject>();
	gameObject->AddComponent<rift2d::FPSComponent>();
	
	scene.Add(std::move(gameObject));

	

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
