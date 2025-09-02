#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "ContentBrowserState.h"

namespace SliceEngine
{
	class EditorState
	{
		std::unique_ptr<ContentBrowserState> contentBrowserState;

	public:
		void Init();

		void RebuildDirectory();
	};

}

#endif