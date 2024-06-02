#pragma once
#include <string_view>
namespace riftSettings
{
	constexpr int WINDOW_WIDTH = 960;
	constexpr int WINDOW_HEIGHT = 640;
	constexpr uint16_t TILE_WIDTH = 64;
	constexpr uint16_t TILE_HEIGHT = 64;
	constexpr uint16_t NR_ROWS = 10;
	constexpr uint16_t NR_COLS = 15;

	//credits Alex Kougentakos, Odyssey engine
	constexpr float PPM = 100.0f;  // pixels per meter
	constexpr float MPP = 1.0f / PPM;  // meters per pixel

	constexpr std::string_view SOUND_PATH = "../Data/sounds/";
}
