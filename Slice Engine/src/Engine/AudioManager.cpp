#include "AudioManager.h"

namespace SliceEngine
{
	void AudioManager::Init()
	{
		SLICE_LOG("Initializing FMOD Studio.");
	}

	void AudioManager::Exit()
	{
		SLICE_LOG("Shutting down FMOD Studio.");
	}
}