#include "../Slice_pch.h"
#include "App.h"

namespace SliceEngine
{
	void App::Init()
	{
		isRunning = true;
		appWindow.CreateDefaultWindow();
	}

	void App::Update()
	{
		while (!appWindow.isWindowClosed())
		{
			glfwPollEvents();

			static int wasRPressed = 0;
			int isRPressed = glfwGetKey(appWindow.GetWindow(), GLFW_KEY_R);

			if (isRPressed && !wasRPressed)
			{
				appWindow.ResizeWindow();
			}

			static int wasFPressed = 0;
			int isFPressed = glfwGetKey(appWindow.GetWindow(), GLFW_KEY_F);

			if (isFPressed && !wasFPressed)
			{
				static bool isFullscreen = false;
				isFullscreen = !isFullscreen;
				appWindow.SetFullscreen(isFullscreen);
			}

			wasRPressed = isRPressed;
			wasFPressed = isFPressed;
			glfwSwapBuffers(appWindow.GetWindow());

		}
	}

	void App::Exit()
	{
		glfwTerminate();
	}
}