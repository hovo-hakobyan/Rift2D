#pragma once
#include <filesystem>
#include <functional>
#include <mutex>
#include <queue>
#include <SDL_mixer.h>
#include <SDL_syswm.h>
#include <unordered_set>

#include "Interfaces.h"

namespace rift2d
{
	class SDLSoundSystem final : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override = default;
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;
		void play(const soundId id, float volume = 1.f) override;
		void setPath(const std::string& dataPath) override;
		void addSoundMapping(int id, const std::string& filename) override;
		
	private:

		struct MixChunkDeleter
		{
			void operator()(Mix_Chunk* chunk) const
			{
				Mix_FreeChunk(chunk);
			}
		};
		using MixChunkRAII = std::unique_ptr<Mix_Chunk, MixChunkDeleter>;

		int m_audioRate{18000};
		UINT16 m_audioFormat{AUDIO_S16SYS};
		int m_audioChannels{1};
		int m_audioBuffers{4096};
		std::filesystem::path m_dataPath;

		static float max_volume;
		static float min_volume;

		std::queue<std::function<void()>> m_soundQueue;
		std::unordered_set<int> m_queuedSounds;
		std::mutex m_queueMutex;
		std::condition_variable m_cvShouldProcess;
		std::jthread m_soundThread;

		std::unordered_map<int, std::string> m_soundMap;
		std::unordered_map<int, MixChunkRAII> m_soundCache;

		void playSound(const soundId id, float volume);
		void loadSound(int id);
		void processSoundQueue();
	};


}
