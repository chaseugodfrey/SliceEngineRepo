#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "WindowTypes.h"
#include "EditorState.h"

namespace SliceEngine
{

	class WindowManager
	{
		std::shared_ptr<EditorState> editorState;

	public:
		
		std::vector<std::unique_ptr<EditorWindow>> list;
		void Init(EditorState& editorState);
		void Render();

		template <typename T>
		void AddWindow(EditorState& editorState);

	};

	template <typename T>
	void WindowManager::AddWindow(EditorState& editorState)
	{
		list.push_back(std::make_unique<T>(editorState));
	}

}



#endif