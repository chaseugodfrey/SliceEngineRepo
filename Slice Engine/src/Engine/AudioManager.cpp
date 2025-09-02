#include "AudioManager.h"

namespace SliceEngine
{
	void AudioManager::Init()
	{
		SLICE_LOG("Initializing FMOD Studio.");
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