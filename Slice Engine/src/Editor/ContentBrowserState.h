#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>
#include <map>

namespace SliceEngine
{
	struct DirectoryNode
	{
		std::string fileName;
		bool isDirectory = false;
		std::filesystem::path path;
		DirectoryNode* parent = nullptr;
		std::map<std::string, DirectoryNode> children;
	};

	struct ContentBrowserState
	{
		std::unique_ptr<DirectoryNode> root;
		bool openRenameFile;

		ContentBrowserState() : openRenameFile(false)
		{
			root = std::make_unique<DirectoryNode>();

			root->path = std::filesystem::path(ASSET_DIR);
			root->fileName = "Assets";
			root->isDirectory = true;
		}
	};
}

#endif