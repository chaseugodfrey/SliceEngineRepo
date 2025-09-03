#ifndef EDITOR_SCENE_VIEW_H
#define EDITOR_SCENE_VIEW_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class SceneView : public EditorWindow
	{
	public:
		void Draw() override final;
	};
}

#endif