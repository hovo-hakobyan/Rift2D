#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include "Singleton.h"
#include "Texture2D.h"
#include "Font.h"

namespace std
{
	using FontKey = std::pair<std::string, int>;
	template<> struct hash<FontKey>
	{
		std::size_t operator()(const FontKey& key) const noexcept
		{
			const size_t hash1 = std::hash<std::string>()(key.first);
			const size_t hash2 = std::hash<int>()(key.second);
			return hash1 ^ (hash2 << 1);
		}
	};
}

namespace rift2d
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		

		~ResourceManager() override;
		void init(const std::filesystem::path& data);
		Texture2D* loadTexture(const std::string& file) const;
		std::unique_ptr<Texture2D> createFontTexture(Font* font, const SDL_Color& color, const std::string& text);
		Font* loadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;

		ResourceManager() = default;
		std::filesystem::path m_dataPath;
		mutable std::unordered_map<std::string, std::unique_ptr<Texture2D>> m_textureCache;
		mutable std::unordered_map<std::FontKey, std::unique_ptr<Font>> m_fontCache;
	};
}
