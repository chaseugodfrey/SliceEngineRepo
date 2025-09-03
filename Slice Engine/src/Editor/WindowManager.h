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
		void Init(EditorState& state);
		void Render();

		template <typename T>
		void AddWindow();

	};

	template <typename T>
	void WindowManager::AddWindow()
	{
		list.push_back(std::make_unique<T>(EditorState& state));
	}

}



#endif