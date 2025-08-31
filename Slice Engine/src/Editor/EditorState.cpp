#include "EditorState.h"

namespace SliceEngine
{
	void EditorState::Init()
	{
		contentBrowserState = std::make_unique<ContentBrowserState>();
		
	}
}