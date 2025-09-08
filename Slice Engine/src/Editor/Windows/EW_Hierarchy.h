#ifndef EDITOR_HIERARCHY_H
#define EDITOR_HIERARCHY_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class EditorState;

	class Hierarchy : public EditorWindow
	{
	public:
		Hierarchy(EditorState& editorState);
		void Draw() override final;
	};
}

#endif