#include "../Slice_pch.h"
#include "App.h"

namespace SliceEngine
{
	void App::Init()
	{
		if (!glfwInit())
			return;

		isRunning = true;
		appWindow.CreateDefaultWindow();
	}

	void App::Update()
	{
		while (isRunning && !appWindow.isWindowClosed())
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

			Vec2f vec1{ 232, -14 };
			Vec2f vec2 = vec1.normal();
			Vec2f vec3 = vec1.normalUnit();

			SLICE_LOG_VALUES(vec2, vec3);

			glfwSwapBuffers(appWindow.GetWindow());

		}
	}

	void App::Exit()
	{
		glfwTerminate();
	}
}