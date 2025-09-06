#ifndef EDITOR_SCENE_VIEW_H
#define EDITOR_SCENE_VIEW_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class EditorState;

	class SceneView : public EditorWindow
	{
	public:
		SceneView(EditorState& editorState);
		void Draw() override final;
	};
}

#endif