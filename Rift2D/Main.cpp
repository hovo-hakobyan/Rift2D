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
#include "SpriteComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"
#include <filesystem>
#include "InputManager.h"
#include "MoveCommand.h"
#include "ShootCommand.h"

namespace fs = std::filesystem;

void load()
{
	auto& scene = rift2d::SceneManager::GetInstance().createScene("Demo");

	//Resources
	auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 36);

	//Background
	auto gameObject = std::make_unique<rift2d::GameObject>(&scene);
	auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("background.tga");
	scene.add(std::move(gameObject));

	// Programming 4 Text
	gameObject = std::make_unique<rift2d::GameObject>(&scene);
	gameObject->addComponent<rift2d::TextComponent>("Programming 4 Assignment", font);
	gameObject->getTransform()->setLocalPosition(80.f, 50.f,1.f);
	scene.add(std::move(gameObject));

	//Logo
	gameObject = std::make_unique<rift2d::GameObject>(&scene);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("logo.tga");
	gameObject->getTransform()->setLocalPosition(216.f, 180.f,1.f);
	scene.add(std::move(gameObject));

	//FPS 
	gameObject = std::make_unique<rift2d::GameObject>(&scene);
	gameObject->addComponent<rift2d::FPSComponent>();
	scene.add(std::move(gameObject));

	gameObject = std::make_unique<rift2d::GameObject>(&scene);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");
	gameObject->getTransform()->setLocalPosition(30.f, 150.f, 1.f);
	//rift2d::InputManager::GetInstance().bindAction(rift2d::GamepadKey::A, 0, rift2d::InputEvent::Down,std::make_unique<rift2d::ShootCommand>(gameObject.get()));
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::LThumbStick, 0, std::make_unique<rift2d::MoveCommand>(gameObject.get(),150.f));
	scene.add(std::move(gameObject));

	gameObject = std::make_unique<rift2d::GameObject>(&scene);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");
	gameObject->getTransform()->setLocalPosition(30.f, 180.f, 1.f);

	scene.add(std::move(gameObject));


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
