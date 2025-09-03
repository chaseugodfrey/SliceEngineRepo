#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include "../EditorWindow.h"
#include "../EditorState.h"
#include "../ContentBrowserState.h"

namespace SliceEngine
{
	class ContentBrowser : public EditorWindow
	{
		//ContentBrowserState& contentBrowser;

		//ContentBrowser(EditorState& editorState);
	public:
		void Draw() override final;
	};
}

#endif