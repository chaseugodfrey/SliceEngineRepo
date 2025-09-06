#ifndef EDITOR_GAME_VIEW_H
#define EDITOR_GAME_VIEW_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class EditorState;

	class GameView : public EditorWindow
	{
		EditorState& editorState;
	public:
		GameView(EditorState& editorState);
		void Draw() override final;
	};
}

#endif