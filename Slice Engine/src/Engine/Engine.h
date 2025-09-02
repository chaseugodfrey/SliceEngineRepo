#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "InputSystem.h"
#include "AudioManager.h"

#ifdef EDITOR
#include "../Editor/Editor.h"
#endif

namespace SliceEngine
{
	class Engine
	{
		GLFWwindow* window;
		bool isRunning;
		
		std::unique_ptr<InputSystem> inputs;
		std::unique_ptr<AudioManager> audio;
		
#ifdef EDITOR
		std::unique_ptr<Editor> editor;
#endif
	public:
		void Init();
		void Update();
		void Exit();

	};
}

#endif 