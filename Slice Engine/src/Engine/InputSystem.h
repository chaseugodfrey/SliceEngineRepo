#ifndef SLICE_INPUTS_H
#define SLICE_INPUTS_H

namespace SliceEngine
{
	class InputSystem
	{
		double mouse_x;
		double mouse_y;

	public:

		InputSystem();
		void Init();
		void Update(GLFWwindow* window);
	};
}

#endif