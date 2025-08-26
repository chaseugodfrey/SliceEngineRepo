#ifndef WINDOW_H
#define WINDOW_H

#include "glfw/include/glfw3.h"

namespace SliceEngine
{
	class Window
	{
	public:
		static GLFWwindow* CreateWindow();
		static void ResizeWindow(GLFWwindow* window, int width, int height);
		static void CloseWindow(GLFWwindow* window);
	};
}

#endif