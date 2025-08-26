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

	}

	void Engine::Update()
	{
		while (isRunning)
		{
			glfwPollEvents();

			// Main Body
			inputs->Update(window);
			//

			if (glfwWindowShouldClose(window))
				isRunning = false;
		}
	}

	void Engine::Exit()
	{
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}