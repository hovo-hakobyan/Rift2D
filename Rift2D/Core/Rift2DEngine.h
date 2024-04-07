#pragma once
#include <functional>
#include <filesystem>

namespace rift2d
{
	class Rift2DEngine final
	{
		
	public:
		explicit Rift2DEngine(const std::filesystem::path& dataPath);
		~Rift2DEngine();
		void run(const std::function<void()>& load);

		Rift2DEngine(const Rift2DEngine& other) = delete;
		Rift2DEngine(Rift2DEngine&& other) = delete;
		Rift2DEngine& operator=(const Rift2DEngine& other) = delete;
		Rift2DEngine& operator=(Rift2DEngine&& other) = delete;

		static void quitGame() { m_shouldQuit = true; }

	private:
		static bool m_shouldQuit;
	};
}