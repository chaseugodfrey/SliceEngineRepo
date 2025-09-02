#include "EditorState.h"

namespace SliceEngine
{
	void EditorState::RebuildDirectory()
	{
		std::filesystem::path current_path = ASSET_DIR;

		for (const auto& entry : std::filesystem::directory_iterator(current_path))
		{
			
		}

		contentBrowserState->current = contentBrowserState->root;
	}

	void EditorState::Init()
	{
		contentBrowserState = std::make_unique<ContentBrowserState>();
		
	}
}