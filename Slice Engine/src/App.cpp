#include "pch.h"
#include "App.h"
#include "TestClass.h"

namespace SliceEngine
{
	void App::Init()
	{
		if (!glfwInit())
			return;

		isRunning = true;
		appWindow.CreateDefaultWindow();

		engine = std::make_unique<Engine>();
		engine->Init();

#ifdef EDITOR
		editor.Init();
#endif
	}

	void App::Update()
	{
		while (isRunning && !appWindow.isWindowClosed())
		{
			glfwPollEvents();

			glfwSwapBuffers(appWindow.GetWindow());
		}
	}

	void App::Exit()
	{
		glfwTerminate();
	}
}