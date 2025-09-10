#ifndef EDITOR_CONTENT_BROWSER_H
#define EDITOR_CONTENT_BROWSER_H

#include "../EditorWindow.h"
#include "../ContentBrowserState.h"

namespace SliceEngine
{
	// forward declarations
	class EditorState;
	class ContentBrowserState;

	class ContentBrowser : public EditorWindow
	{
		EditorState& editorState;

	public:
		ContentBrowser(EditorState& editorState);

		//void Init();

		void Draw() override final;

		void DisplayFolders(DirectoryNode& node);

		void DisplayItems(DirectoryNode& node);

		void SelectFile(DirectoryNode& node);

		void RenameFilePopup(DirectoryNode& node);
		
		
	};
}

#endif