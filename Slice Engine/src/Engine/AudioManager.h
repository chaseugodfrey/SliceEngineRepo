#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H
#include "../ThirdParty/fmod/include/fmod.hpp"
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
	}

	class AudioManager
	{
		//FMOD::Studio::System* system;
		FMOD::System* mSoundSystem;
		FMOD::Sound* sound;
		std::vector<std::unique_ptr<SoundTrack>> mSound[SOUND_MAX_SOUNDS];
		std::unordered_map<SoundCategory, float> mCategoryVolumes;
		const float defaultVolume = 1.0f;
		

	public:
		enum InternalSound
		{
			SOUND_INGAME,
			SOUND_INMENU,
			SOUND_BGM,
			SOUND_EDITOR,
			SOUND_MAX_SOUNDS
		};

		void Init();
		void Update();
		void Exit();

		void PlaySound();
		void StopSound();
		void SwitchSound();
		
		
	};
}

#endif