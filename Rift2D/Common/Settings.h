#pragma once
#include <string_view>
namespace settings
{
	constexpr int WINDOW_WIDTH = 960;
	constexpr int WINDOW_HEIGHT = 600;
	constexpr uint16_t TILE_WIDTH = 64;
	constexpr uint16_t TILE_HEIGHT = 64;

	//credits Alex Kougentakos, Odyssey engine
	constexpr float PPM = 100.0f;  // pixels per meter
	constexpr float MPP = 1.0f / PPM;  // meters per pixel

	constexpr std::string_view SOUND_PATH = "../Data/sounds/";
}
