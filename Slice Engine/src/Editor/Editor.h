#ifndef EDITOR_H
#define EDITOR_H

struct GLFWwindow;

namespace SliceEngine
{
	class Editor
	{
	public:

		void Init(GLFWwindow* window);
		void Update();
		void Render(GLFWwindow* window);
		void Exit();

		void RenderMainMenuBar();

	};
}

#endif