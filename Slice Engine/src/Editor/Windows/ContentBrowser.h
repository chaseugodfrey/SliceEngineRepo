#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class ContentBrowser : public EditorWindow
	{
		void Draw() override final;
	};
}

#endif