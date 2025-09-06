#ifndef EDITOR_CONTENT_BROWSER_H
#define EDITOR_CONTENT_BROWSER_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	// forward declarations
	class EditorState;
	class ContentBrowserState;

	class ContentBrowser : public EditorWindow
	{
		ContentBrowserState& contentBrowserState;

	public:
		ContentBrowser(EditorState& editorState);

		void Init();

		void Draw() override final;

		void DisplayFolders(ContentBrowserState& contentBrowser);
	};
}

#endif