#include <stdexcept>
#include <sstream>
#include <iostream>
#include <thread>

#if WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Rift2DEngine.h"
#include <glm/glm.hpp>
#include "InputManager.h"
#include "Locator.h"
#include "Physics.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SDLSoundSystem.h"

SDL_Window* g_window{};
bool rift2d::Rift2DEngine::m_shouldQuit = false;

void LogSDLVersion(const std::string& message, const SDL_version& v)
{
#if WIN32
	std::stringstream ss;
	ss << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
	static_cast<rift2d::Rift2DEngine*>(arg)->RunOneFrame();
}
#endif
namespace fs = std::filesystem;
// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	LogSDLVersion("We compiled against SDL version ", version);

	SDL_GetVersion(&version);
	LogSDLVersion("We linked against SDL version ", version);

	SDL_IMAGE_VERSION(&version);
	LogSDLVersion("We compiled against SDL_image version ", version);

	version = *IMG_Linked_Version();
	LogSDLVersion("We linked against SDL_image version ", version);

	SDL_TTF_VERSION(&version)
	LogSDLVersion("We compiled against SDL_ttf version ", version);

	version = *TTF_Linked_Version();
	LogSDLVersion("We linked against SDL_ttf version ", version);
}

rift2d::Rift2DEngine::Rift2DEngine(const std::filesystem::path &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment - Howhannes Hakobyan 2DAE09",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		960,
		600,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().init(g_window);
	ResourceManager::GetInstance().init(dataPath);
	SDL_GL_SetSwapInterval(1); //Enable VSync

	//Init audo system

	if (SDL_Init(SDL_INIT_AUDIO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init_Audio Error: ") + SDL_GetError());
	}
	ServiceLocator::registerSoundSystem(std::make_unique<SDLSoundSystem>());

	fs::path soundLocation = "./Data/sounds";
	if (!fs::exists(soundLocation))soundLocation = "../Data/sounds/";
	else soundLocation = "";
	ServiceLocator::getSoundSystem().setPath(soundLocation.string());
		
	//init physics
	Physics::GetInstance().init();
}

rift2d::Rift2DEngine::~Rift2DEngine()
{
	Physics::GetInstance().destroy();
	Renderer::GetInstance().destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void rift2d::Rift2DEngine::run(const std::function<void()>& load)
{
	load();
#ifndef __EMSCRIPTEN__

	auto& sceneManager = SceneManager::GetInstance();

	sceneManager.init();
	InputManager::GetInstance().init();
	auto& timeManager = TimeManager::GetInstance();
	using namespace std::chrono;

	auto lastTime = high_resolution_clock::now();
	timeManager.m_deltaTime = 1.0f / 144.f;
	timeManager.m_fixedTime = 1.f / 60.f;
	const float minDeltaTime = 0.001f;

	float lag = 0.f;

	while (!m_shouldQuit)
	{
		const auto currentTime = high_resolution_clock::now();
		const float deltaTime = duration<float>(currentTime - lastTime).count();
		timeManager.m_deltaTime = glm::max(deltaTime, minDeltaTime);
		lastTime = currentTime;
		lag += timeManager.m_deltaTime;

		m_shouldQuit = !InputManager::GetInstance().processInput();

		while (lag >= timeManager.m_fixedTime)
		{
			sceneManager.fixedUpdate();
			Physics::GetInstance().update();
			lag -= timeManager.m_fixedTime;
		}

		sceneManager.update();
		sceneManager.lateUpdate();
		sceneManager.frameCleanup();
		Renderer::GetInstance().render();
		
	}
	sceneManager.end();
		
#else
	emscripten_set_main_loop_arg(&LoopCallback, this, 0, true);
#endif
}
