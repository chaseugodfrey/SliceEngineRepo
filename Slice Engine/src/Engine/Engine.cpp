#include <pch.h>
#include "Engine.h"

namespace SliceEngine
{
	void Engine::Init()
	{
		SLICE_LOG("Initializing Slice Engine.");

		// Initialize glfw
		glfwInit();

		// Create Window
		window = Window::CreateWindow();

		// Set up Engine Systems
		isRunning = true;

		inputs = std::make_unique<InputSystem>();

#ifdef EDITOR
		editor = std::make_unique<Editor>();
		editor->Init(window);
#endif

	}

	void Engine::Update()
	{
		while (isRunning)
		{
			glfwMakeContextCurrent(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			// Main Body
			inputs->Update(window);
			//

#ifdef EDITOR
			editor->Render(window);
#endif


			glfwSwapBuffers(window);

			if (glfwWindowShouldClose(window))
				isRunning = false;
		}
	}

	void Engine::Exit()
	{

#ifdef EDITOR
		editor->Exit();
#endif
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}


}