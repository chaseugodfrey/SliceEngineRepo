#include "EditorState.h"

namespace SliceEngine
{
	void EditorState::ResetRootDirectory()
	{
		contentBrowserState->root = std::make_unique<DirectoryNode>();
		contentBrowserState->root->path = ASSET_DIR;
		contentBrowserState->root->fileName = "Assets";
	}

	void EditorState::CreateDirectory(DirectoryNode& node)
	{
		if (node.path.has_extension())
		{
			return;
		}

		for (const auto& entry : std::filesystem::directory_iterator(node.path))
		{
			DirectoryNode child = {};
			child.path = entry.path();
			child.parent = &node;
			child.fileName = entry.path().filename().string();

			if (entry.is_directory())
			{
				node.children.push_back(child);
			}

			CreateDirectory(child);

		}
		return;
	}

	void EditorState::Init()
	{
		contentBrowserState = std::make_unique<ContentBrowserState>();
		
	}
}