#ifndef EDITOR_CONTENT_BROWSER_H
#define EDITOR_CONTENT_BROWSER_H

#include "../EditorWindow.h"
#include "../EditorState.h"
#include "../ContentBrowserState.h"

namespace SliceEngine
{
	class ContentBrowser : public EditorWindow
	{
		EditorState& editorState;


	public:
		ContentBrowser(EditorState& editorState);

		void Init();

		void Draw() override final;

		void DisplayFolders(std::unique_ptr<DirectoryNode>& node);
	};
}

#endif