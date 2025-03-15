#include "../Slice_pch.h"
#include "AppWindow.h"

static std::vector<std::pair<int, int>> sizes;
size_t index{};

namespace SliceEngine
{
	void AppWindow::CreateDefaultWindow()
	{
		glfwInit();
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
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