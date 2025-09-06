#ifndef EDITOR_H
#define EDITOR_H

struct GLFWwindow;

#include "../Engine/ECS/ECSTypes.h"
#include "WindowManager.h"
#include "EditorState.h"


namespace SliceEngine
{
	class Engine;

	class Editor
	{
		Engine* engine;
		std::unique_ptr<EditorState> editorState;
		std::unique_ptr<WindowManager> windowManager;

		void InitImGUI(GLFWwindow* window);
		void InitEditorState();
		void InitWindowManager(EditorState& editorState);

	public:

		Editor(Engine* r_engine);
		void Init(GLFWwindow* window);
		void Update();
		void Render(GLFWwindow* window);
		void Exit();
	};
}

#endif