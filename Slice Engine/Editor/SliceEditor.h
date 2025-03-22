#ifndef SLICE_EDITOR_H
#define SLICE_EDITOR_H

struct GLFWwindow;

namespace SliceEngine
{

	class Editor
	{

		void DisplayMainMenu();

	public:

		void Init(GLFWwindow* window);
		void Setup();
		void Update(GLFWwindow* window);
		void Render();
		void Exit();
	};
}

#endif