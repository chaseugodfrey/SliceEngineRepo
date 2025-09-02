#include "AudioManager.h"

namespace SliceEngine
{
	void AudioManager::Init()
	{
		SLICE_LOG("Initializing FMOD Studio.");
	}

	void AudioManager::LoadSound(const std::string& soundName, const std::string& soundFile)
	{
		FMOD_MODE eMode = FMOD_DEFAULT | FMOD_LOOP_NORMAL;
		FMOD::Sound* sound{ nullptr };
		mSoundSystem->createSound(soundFile.c_str(), eMode, nullptr, &sound);
	}

	void AudioManager::Update()
	{
		
	}

	void AudioManager::PlaySound(const std::string& soundName, SoundCategory category, InternalSound internalCategory, bool isLoop, float volume)
	{

	}
	

	void AudioManager::Exit()
	{
		SLICE_LOG("Shutting down FMOD Studio.");
	}
}