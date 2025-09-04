#ifndef EDITOR_GAME_VIEW_H
#define EDITOR_GAME_VIEW_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class GameView : public EditorWindow
	{
	public:
		void Draw() override final;
	};
}

#endif