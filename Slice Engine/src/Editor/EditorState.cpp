#include "EditorState.h"

namespace SliceEngine
{
	void EditorState::Init()
	{
		contentBrowserState = std::make_unique<ContentBrowserState>();
		
	}

	void EditorState::RebuildDirectory(DirectoryNode& node)
	{
		ResetRootDirectory(node);
		CreateDirectory(node);
	}

	void EditorState::ResetRootDirectory(DirectoryNode& node)
	{
		node.children.clear();
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
			child.isDirectory = entry.is_directory();

			node.children.push_back(child);


			CreateDirectory(child);

		}
		return;
	}

	void EditorState::RenameFile(DirectoryNode& node)
	{
		std::filesystem::path& fileName = node.path.filename();
	}
}