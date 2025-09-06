#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "ContentBrowserState.h"
#include "EditorConsole.h"

namespace SliceEngine
{
	class EditorState
	{
	public:
		std::unique_ptr<ContentBrowserState> contentBrowserState;
		std::unique_ptr<EditorConsole> console;
		
		void Init();

		void RebuildDirectory();
	};

}

#endif