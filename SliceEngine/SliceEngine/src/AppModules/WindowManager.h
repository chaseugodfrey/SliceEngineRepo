#ifndef SLICE_WINDOW_MANAGER
#define SLICE_WINDOW_MANAGER

#include "Common.h"
#include <GLFW/glfw3.h>


namespace SliceEngine
{
	class WindowManager : IModule
	{
		GLFWwindow* window;

	public:
		WindowManager();
		void Init() override;
		void Update() override;
		void Exit() override;
	};
}

#endif