#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "InputSystem.h"

namespace SliceEngine
{
	class Engine
	{
		GLFWwindow* window;
		bool isRunning;
		
		std::unique_ptr<InputSystem> inputs;

	public:
		void Init();
		void Update();
		void Exit();
	};
}

#endif 