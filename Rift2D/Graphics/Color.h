#pragma once
#include <cstdint>

namespace rift2d
{
	struct RiftColor
	{
		uint8_t r{}, g{}, b{}, a{};

		/// <summary>
/// Range is [0,255]
/// </summary>
		explicit  RiftColor(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255)
			: r(red), g(green), b(blue), a(alpha) {}
		RiftColor()= default;
	};
}
