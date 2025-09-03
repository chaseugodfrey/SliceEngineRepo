#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include "../EditorWindow.h"
#include "../ContentBrowserState.h"

namespace SliceEngine
{
	class ContentBrowser : public EditorWindow
	{
	public:
		void Draw() override final;
	};
}

#endif