#pragma once
#include <string>
struct _TTF_Font;
namespace rift2d
{
	/**
	 * Simple RAII wrapper for a _TTF_Font
	 */
	class Font final
	{
	public:
		_TTF_Font* getFont() const;
		unsigned int getFontSize() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		_TTF_Font* m_font;
		unsigned int m_fontSize{};
	};
}
