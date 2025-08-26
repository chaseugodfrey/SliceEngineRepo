#include "pch.h"
#include "Engine.h"

namespace SliceEngine
{
	void Engine::Init()
	{
		SLICE_LOG("Initializing Slice Engine.");
		glfwInit();
		window = Window::CreateWindow();
	}

	void Engine::Update()
	{
		while (1)
		{
			glfwPollEvents();
			glfwWindowShouldClose(window);
		}
	}

	void Engine::Exit()
	{
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}