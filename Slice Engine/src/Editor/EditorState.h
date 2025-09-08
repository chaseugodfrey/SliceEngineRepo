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
		std::unique_ptr<EditorConsole> console;
		
		void Init();

		void RebuildDirectory();
	};

}

#endif