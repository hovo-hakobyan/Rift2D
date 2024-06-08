#pragma once
#include <memory>
#include "Interfaces.h"

namespace rift2d
{
	class SDLSoundSystem final : public ISoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;
		SDLSoundSystem(const SDLSoundSystem&) = delete;
		SDLSoundSystem(SDLSoundSystem&&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&) = delete;
		SDLSoundSystem& operator= (const SDLSoundSystem&&) = delete;

		void play(const soundId id, float volume = 1.f) override;
		void setPath(const std::string& dataPath) override;
		void addSoundMapping(int id, const std::string& filename) override;

		void mute() override;
		void clearSounds() override;

		
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};


}
