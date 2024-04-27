#include "SDLSoundSystem.h"

#include "Exception.h"
#include "SDL_mixer.h"
#include <direct.h>

float rift2d::SDLSoundSystem::max_volume = 1.f;
float rift2d::SDLSoundSystem::min_volume = 0.f;

rift2d::SDLSoundSystem::SDLSoundSystem()
{
	if (Mix_OpenAudio(m_audioRate, m_audioFormat, m_audioChannels, m_audioBuffers) != 0)
	{
		THROW_RIFT_EXCEPTION(Mix_GetError(), RiftExceptionType::Error);
	}
	m_soundThread = std::jthread{ &SDLSoundSystem::processSoundQueue,this };
}

void rift2d::SDLSoundSystem::play(const soundId id ,float volume )
{
	{
		std::lock_guard lock(m_queueMutex);
		if(!m_queuedSounds.contains(id))
		{
			m_soundQueue.emplace([this, id, volume] {playSound(id, volume); });
			m_queuedSounds.insert(id);
			std::cout << "added sound to the queue\n";
		}
		else
		{
			std::cout << "Sound already in the queue\n";
		}
	
	}
	
	m_cvShouldProcess.notify_one();
}

void rift2d::SDLSoundSystem::setPath(const std::string& dataPath)
{
	if (dataPath.empty()) THROW_RIFT_EXCEPTION("Data path to sounds cannot be found", RiftExceptionType::Error);
	m_dataPath = dataPath;
}

void rift2d::SDLSoundSystem::addSoundMapping(int id, const std::string& filename)
{
	m_soundMap[id] = filename;
}


void rift2d::SDLSoundSystem::playSound(const soundId id, float volume)
{
	if (!m_soundCache.contains(id)) loadSound(id);

	if(const auto it = m_soundCache.find(id); it != m_soundCache.end() && it->second)
	{
		volume = std::max(min_volume, volume);
		volume = std::min(max_volume, volume);

		const int sdlVolume = static_cast<int>(volume * MIX_MAX_VOLUME);
		Mix_VolumeChunk(it->second.get(), sdlVolume);
		Mix_PlayChannel(-1, it->second.get(), 0);
		std::cout << "sound played with the id " << id << '\n';
	}

}

void rift2d::SDLSoundSystem::loadSound(int id)
{
	const auto soundInfo = m_soundMap.find(id);
	if (soundInfo == m_soundMap.end())
	{
		std::cout << "Sound ID " << id << " not found.\n";
		return;
	}
	const auto fullPath = m_dataPath / soundInfo->second;
	Mix_Chunk* sound = Mix_LoadWAV(fullPath.string().c_str());
	if (!sound)  std::cout << "Failed to load sound: " << SDL_GetError() << '\n';
	else m_soundCache[id] = MixChunkRAII(sound);
}

[[noreturn]] void rift2d::SDLSoundSystem::processSoundQueue()
{
	std::unique_lock lock(m_queueMutex);
	while (true)
	{
		std::cout << "Waiting on cv\n";
		m_cvShouldProcess.wait(lock, [&] { return !m_soundQueue.empty(); });
		std::cout << "Start processing queue\n";
		while (!m_soundQueue.empty())
		{
			auto task = m_soundQueue.front();
			m_soundQueue.pop();
			m_queuedSounds.erase(m_queuedSounds.begin());
			lock.unlock();
			task();
			lock.lock();
		}
		std::cout << "Done processing queue\n";
	}
}
