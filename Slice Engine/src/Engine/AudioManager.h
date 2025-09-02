#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#include "../ThirdParty/fmod/include/fmod.hpp"
#include "../SoundSystem.h"
#include <vector>
#include <unordered_map>


namespace SliceEngine
{
	enum class SoundCategory
	{
		SFX,
		BGM,
		UI,
		Editor
	};

	struct SoundTrack
	{
		FMOD::Sound* sound = nullptr;
		FMOD::Channel* channel = nullptr;
		float defaultSoundVolume = 1.0f;
		float currentSoundVolume = 1.0f;
		SoundCategory category = SoundCategory::SFX;
		bool isLooping = false;
		bool isPaused = false;
		bool muffle = false;
	};

	class AudioManager
	{
		enum InternalSound
		{
			SOUND_INGAME,
			SOUND_INMENU,
			SOUND_BGM,
			SOUND_EDITOR,
			SOUND_MAX_SOUNDS
		};

		//FMOD::Studio::System* system;
		FMOD::System* mSoundSystem;
		const int MAX_CHANNELS = 256;

		FMOD::Sound* sound;
		//std::vector<std::unique_ptr<SoundTrack>> mSound[SOUND_MAX_SOUNDS];
		std::unordered_map<std::string, std::unique_ptr<SoundTrack>> mLoadedSounds;
		std::unordered_map<SoundCategory, float> mCategoryVolumes;
		const float defaultVolume = 1.0f;

		

	public:
		static AudioManager& Get()
		{
			static AudioManager instance;
			return instance;
		}


		void Init();
		void Update();
		void Exit();

		void LoadSound(const std::string& soundName, const std::string& soundFile, bool is3D, bool loop = true);
		void PlaySound(const std::string& soundName, SoundCategory category, InternalSound internalCategory, bool isLoop, float volume);
		void StopSound();
		void SwitchSound();
		
	private:
		AudioManager() = default;
		~AudioManager() = default;

		AudioManager(const AudioManager&) = delete;
		AudioManager& operator=(const AudioManager&) = delete;
		
	};
}

#endif