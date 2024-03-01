#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include "Singleton.h"

namespace rift2d
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void init(const std::filesystem::path& data);
		std::shared_ptr<Texture2D> loadTexture(const std::string& file) const;
		std::shared_ptr<Font> loadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::filesystem::path m_dataPath;
	};
}
