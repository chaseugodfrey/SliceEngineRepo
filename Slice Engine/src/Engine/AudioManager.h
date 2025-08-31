#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

namespace SliceEngine
{
	class AudioManager
	{
		FMOD::Studio::System* system;

	public:
		void Init();
		void Exit();
	};
}

#endif