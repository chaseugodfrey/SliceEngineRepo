#ifndef EDITOR_H
#define EDITOR_H

struct GLFWwindow;

#include "WindowManager.h"
#include "EditorState.h"

namespace SliceEngine
{
	class Editor
	{
		std::unique_ptr<EditorState> editorState;
		std::unique_ptr<WindowManager> windowManager;

		void InitImGUI(GLFWwindow* window);
		void InitEditorState();
		void InitWindowManager(EditorState& editorState);

		void DrawMainMenu();
		void DrawDockspace();

	public:

		void Init(GLFWwindow* window);
		void Update();
		void Render(GLFWwindow* window);
		void Exit();
	};
}

#endif