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

		if (glewInit() != GLEW_OK)
		{
			SLICE_LOG("BAD");
		}	

		engine = std::make_unique<Engine>();
		engine->Init();

#ifdef EDITOR
		editor.Init(appWindow.GetWindow());
#endif
	}

	void App::Update()
	{
		while (isRunning && !appWindow.isWindowClosed())
		{
			glfwMakeContextCurrent(appWindow.GetWindow());
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
#ifdef EDITOR
			editor.Update(appWindow.GetWindow());
#endif
			glfwSwapBuffers(appWindow.GetWindow());
		}
	}

	void App::Exit()
	{
		glfwTerminate();
	}
}