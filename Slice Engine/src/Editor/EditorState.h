#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "ContentBrowserState.h"

namespace SliceEngine
{
	class EditorState
	{

	public:
		std::unique_ptr<ContentBrowserState> contentBrowserState;
		
		void Init();

		void RebuildDirectory();
	};

}

#endif