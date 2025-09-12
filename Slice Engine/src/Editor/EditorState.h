#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "ContentBrowserState.h"
#include "EditorConsole.h"
#include "../Engine/ECS/ECSTypes.h"

namespace SliceEngine
{
	class RenderManager;

	class EditorState
	{
	

	public:
		
		RenderManager* renderManager;
		std::unique_ptr<ContentBrowserState> contentBrowserState;

		DirectoryNode* selectedFolder;
		std::unique_ptr<EditorConsole> console;
		
		EditorState();

		void Init();

		void ResetRootDirectory(DirectoryNode& node);

		void CreateDirectory(DirectoryNode& node);

		void RebuildDirectory(DirectoryNode& node);

		void RenameFile(DirectoryNode& entry, char* newName);

		void OpenFile();

		void DeleteFile(DirectoryNode& entry);

	};

}

#endif