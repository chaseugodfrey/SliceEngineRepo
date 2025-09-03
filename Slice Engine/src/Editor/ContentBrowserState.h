#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>

namespace SliceEngine
{
	struct DirectoryNode
	{
		std::filesystem::path path;
		DirectoryNode* parent;
		std::vector<DirectoryNode> children;
	};

	struct ContentBrowserState
	{
		std::unique_ptr<DirectoryNode> root;
	};
}

#endif