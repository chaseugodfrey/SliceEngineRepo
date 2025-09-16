#ifndef EDITOR_CONTENT_BROWSER_STATE_H
#define EDITOR_CONTENT_BROWSER_STATE_H

#include <filesystem>
#include <map>
#include "./EditorTypes.h"

namespace SliceEngine
{

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