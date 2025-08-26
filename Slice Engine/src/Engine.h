#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"

namespace SliceEngine
{
	class Engine
	{
		GLFWwindow* window;

	public:
		void Init();
		void Update();
		void Exit();
	};
}

#endif 