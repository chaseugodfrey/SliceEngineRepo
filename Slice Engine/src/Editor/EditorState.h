#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "ContentBrowserState.h"

namespace SliceEngine
{
	class EditorState
	{

	public:
		std::unique_ptr<ContentBrowserState> contentBrowserState;

		DirectoryNode* selectedNode = nullptr;
		
		void Init();

		void ResetRootDirectory(DirectoryNode& node);

		void CreateDirectory(DirectoryNode& node);

		void RebuildDirectory(DirectoryNode& node);
	};

}

#endif