#include "../Slice_pch.h"
#include "AppWindow.h"

static std::vector<std::pair<int, int>> sizes;
size_t index{};

namespace SliceEngine
{
	void AppWindow::CreateDefaultWindow()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();

		//glClearColor(0.f, 0.f, 0.f, 1.f);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8); 
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8); 
		glfwWindowHint(GLFW_ALPHA_BITS, 8);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		m_appWindow = glfwCreateWindow(900, 600, "Me", nullptr, nullptr);

		for (int i = 1; i < 6; i++)
		{
			sizes.push_back({ 100 * i, 100 * i });
		}
	}

	void AppWindow::ResizeWindow()
	{
		std::cout << "Attempting to resize Window\n";
		std::pair<int, int> size = sizes[index];
		glfwSetWindowSize(m_appWindow, size.first, size.second);
		
		index = index >= 4 ? 0 : index + 1;
	}

	void AppWindow::SetFullscreen(bool fullscreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);

		static std::pair<int, int> previous_pos{};

		if (fullscreen)
		{
			glfwGetWindowPos(m_appWindow, &previous_pos.first, &previous_pos.second);
			glfwSetWindowMonitor(m_appWindow, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
		}

		else
			glfwSetWindowMonitor(m_appWindow, nullptr, previous_pos.first, previous_pos.second, sizes[index].first, sizes[index].second, GLFW_DONT_CARE);
	}

	bool AppWindow::isWindowClosed()
	{
		return glfwWindowShouldClose(m_appWindow);
	}
	GLFWwindow* AppWindow::GetWindow()
	{
		return m_appWindow;
	}
}