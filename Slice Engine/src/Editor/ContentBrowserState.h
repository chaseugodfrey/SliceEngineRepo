#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>

namespace SliceEngine
{
	struct DirectoryNode
	{
		std::filesystem::path path;
		DirectoryNode* parent = nullptr;
		std::vector<DirectoryNode> children;
	};

	struct ContentBrowserState
	{
		ContentBrowserState()
		{
			root = std::make_unique<DirectoryNode>();

			root->path = std::filesystem::path(ASSET_DIR);
		}
		std::unique_ptr<DirectoryNode> root;
	};
}

#endif