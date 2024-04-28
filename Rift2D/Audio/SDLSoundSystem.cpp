#include "SDLSoundSystem.h"
#include "Exception.h"
#include "SDL_mixer.h"
#include <direct.h>
#include <functional>
#include <mutex>
#include <queue>
#include <SDL_syswm.h>
#include <unordered_set>
#include <filesystem>



class rift2d::SDLSoundSystem::Impl
{
public:
	Impl()
	{
		if (Mix_OpenAudio(m_audioRate, m_audioFormat, m_audioChannels, m_audioBuffers) != 0)
		{
			THROW_RIFT_EXCEPTION(Mix_GetError(), RiftExceptionType::Error);
		}
		m_soundThread = std::jthread{ &SDLSoundSystem::Impl::processSoundQueue,this };
	}

	void play(const soundId id, float volume = 1.f)
	{
		{
			std::lock_guard lock(m_queueMutex);
			if (!m_queuedSounds.contains(id))
			{
				m_soundQueue.emplace([this, id, volume] {playSound(id, volume); });
				m_queuedSounds.insert(id);
			}
		}

		m_cvShouldProcess.notify_one();
	}

	void setPath(const std::string& dataPath)
	{
		if (dataPath.empty()) THROW_RIFT_EXCEPTION("Data path to sounds cannot be found", RiftExceptionType::Error);
		m_dataPath = dataPath;
	}

	void addSoundMapping(int id, const std::string& filename)
	{
		m_soundMap[id] = filename;
	}
private:
	struct MixChunkDeleter
	{
		void operator()(Mix_Chunk* chunk) const
		{
			Mix_FreeChunk(chunk);
		}
	};
	using MixChunkRAII = std::unique_ptr<Mix_Chunk, MixChunkDeleter>;

	int m_audioRate{ 18000 };
	UINT16 m_audioFormat{ AUDIO_S16SYS };
	int m_audioChannels{ 1 };
	int m_audioBuffers{ 4096 };
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

	void playSound(const soundId id, float volume)
	{
		if (!m_soundCache.contains(id)) loadSound(id);

		if (const auto it = m_soundCache.find(id); it != m_soundCache.end() && it->second)
		{
			volume = std::max(min_volume, volume);
			volume = std::min(max_volume, volume);

			const int sdlVolume = static_cast<int>(volume * MIX_MAX_VOLUME);
			Mix_VolumeChunk(it->second.get(), sdlVolume);
			Mix_PlayChannel(-1, it->second.get(), 0);
		}
	}

	void loadSound(int id)
	{
		const auto soundInfo = m_soundMap.find(id);
		if (soundInfo == m_soundMap.end())
		{
			return;
		}
		const auto fullPath = m_dataPath / soundInfo->second;
		Mix_Chunk* sound = Mix_LoadWAV(fullPath.string().c_str());
		if (!sound)  std::cout << "Failed to load sound: " << SDL_GetError() << '\n';
		else m_soundCache[id] = MixChunkRAII(sound);
	}

	[[noreturn]] void processSoundQueue()
	{
		std::unique_lock lock(m_queueMutex);
		while (true)
		{
			m_cvShouldProcess.wait(lock, [&] { return !m_soundQueue.empty(); });

			while (!m_soundQueue.empty())
			{
				auto task = m_soundQueue.front();
				m_soundQueue.pop();
				m_queuedSounds.erase(m_queuedSounds.begin());
				lock.unlock();
				task();
				lock.lock();
			}
		}
	}
};
float rift2d::SDLSoundSystem::Impl::max_volume = 1.0f; 
float rift2d::SDLSoundSystem::Impl::min_volume = 0.0f;  

rift2d::SDLSoundSystem::SDLSoundSystem() :m_pImpl{ std::make_unique<Impl>() } {}
rift2d::SDLSoundSystem::~SDLSoundSystem() = default;


void rift2d::SDLSoundSystem::play(const soundId id ,float volume )
{
	m_pImpl->play(id, volume);
}

void rift2d::SDLSoundSystem::setPath(const std::string& dataPath)
{
	m_pImpl->setPath(dataPath);
}

void rift2d::SDLSoundSystem::addSoundMapping(int id, const std::string& filename)
{
	m_pImpl->addSoundMapping(id, filename);
}
