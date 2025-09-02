#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>

namespace SliceEngine
{
	struct DirectoryNode
	{
		std::filesystem::path path;
	};

	struct ContentBrowserState
	{
		std::vector<DirectoryNode> nodes;
		DirectoryNode* root;
		DirectoryNode* current;
	};
}

#endif