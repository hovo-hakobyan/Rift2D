#include "MenuScene.h"
#include "FPSComponent.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "TextComponent.h"

rift2d::MenuScene::MenuScene():
Scene("MainMenuScene")
{
}

void rift2d::MenuScene::init()
{
	//Resources
	auto font = rift2d::ResourceManager::GetInstance().loadFont("Lingua.otf", 36);

	//Background
	auto gameObject = std::make_unique<rift2d::GameObject>(this);
	auto spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("background.tga");
	add(std::move(gameObject));

	// Programming 4 Text
	gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::TextComponent>("Programming 4 Assignment", font);
	gameObject->getTransform()->setLocalPosition(80.f, 50.f, 1.f);
	add(std::move(gameObject));

	//Logo
	gameObject = std::make_unique<rift2d::GameObject>(this);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("logo.tga");
	gameObject->getTransform()->setLocalPosition(216.f, 180.f, 1.f);
	add(std::move(gameObject));

	//FPS 
	gameObject = std::make_unique<rift2d::GameObject>(this);
	gameObject->addComponent<rift2d::FPSComponent>();
	add(std::move(gameObject));

	gameObject = std::make_unique<rift2d::GameObject>(this);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");
	gameObject->getTransform()->setLocalPosition(30.f, 150.f, 1.f);
	rift2d::InputManager::GetInstance().bindAxis2D(rift2d::GamepadAxis2D::DPad, 0,
		std::make_unique<rift2d::MoveCommand>(gameObject.get(), 300.f));
	add(std::move(gameObject));

	gameObject = std::make_unique<rift2d::GameObject>(this);
	spriteComponent = gameObject->addComponent<rift2d::SpriteComponent>();
	spriteComponent->setTexture("Tom.jpg");
	rift2d::InputManager::GetInstance().bindAxis2D(SDL_SCANCODE_D, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_W,
		std::make_unique<rift2d::MoveCommand>(gameObject.get(), 150.f));
	gameObject->getTransform()->setLocalPosition(30.f, 180.f, 1.f);
	add(std::move(gameObject));
}
