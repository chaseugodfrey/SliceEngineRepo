#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Input/InputSystem.h"
#include "AudioManager.h"
#include "Graphics/ResourceManager.h"
#include "Graphics/RenderManager.h"

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
		std::unique_ptr<ResourceManager> mResource;
		std::unique_ptr<RenderManager> mRender;
		
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