#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>

namespace SliceEngine
{
	struct DirectoryNode
	{
		std::filesystem::path path;
		DirectoryNode* parent = nullptr;
		bool isDirectory = true;
		std::vector<std::unique_ptr<DirectoryNode>> children;
	};

	struct ContentBrowserState
	{
		std::unique_ptr<DirectoryNode> root;

		ContentBrowserState()
		{
			root = std::make_unique<DirectoryNode>();

			root->path = std::filesystem::path(ASSET_DIR);

			CreateDirectory(*root);
		}

		void CreateDirectory(DirectoryNode& node);
	};
}

#endif