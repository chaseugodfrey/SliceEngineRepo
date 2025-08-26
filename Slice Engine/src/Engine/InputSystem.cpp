#include "InputSystem.h"

namespace SliceEngine
{
	InputSystem::InputSystem() :
		mouse_x(0), mouse_y(0)
	{

	}

	void InputSystem::Init()
	{

	}

	void InputSystem::Update(GLFWwindow* window)
	{
		glfwGetCursorPos(window, &mouse_x, &mouse_y);
	}
}