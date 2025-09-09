#include "WindowManager.h"

namespace SliceEngine
{
	void WindowManager::Init(EditorState& editorState)
	{
		AddWindow<ContentBrowser>(editorState);
		AddWindow<SceneView>(editorState);
		AddWindow<GameView>(editorState);
		AddWindow<Hierarchy>(editorState);
		AddWindow<Inspector>(editorState);
		//AddWindow<Console>();
		//AddWindow<Animator>();
		//AddWindow<Profiler>();
		//AddWindow<Animation>();
	}

	void WindowManager::Render()
	{

	}
}
