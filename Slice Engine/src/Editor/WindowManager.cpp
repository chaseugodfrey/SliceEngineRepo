#include "WindowManager.h"

namespace SliceEngine
{
	void WindowManager::Init(EditorState& editorState)
	{
		AddWindow<ContentBrowser>(editorState);
	}

	void WindowManager::Render()
	{

	}
}
