#include "src/Engine/Engine.h"

int main()
{
	SliceEngine::Engine engine{};
	SliceEngine::AudioManager audioManager{};

	engine.Init();
	audioManager.Init();
	audioManager.LoadSound("BGMTest", "BGM_MainMenu_Mix1", false, false);
	audioManager.PlaySound("BGMTest", SliceEngine::SoundCategory::BGM, SliceEngine::AudioManager::InternalSound::SOUND_BGM, false, 0.5f);
	engine.Update();

	engine.Exit();



	return 0;
}
