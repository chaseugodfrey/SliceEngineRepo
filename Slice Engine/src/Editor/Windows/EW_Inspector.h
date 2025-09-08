#ifndef EDITOR_INSPECTOR_H
#define EDITOR_INSPECTOR_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class EditorState;

	class Inspector : public EditorWindow
	{
	public:
		Inspector(EditorState& editorState);
		void Draw() override final;
	};
}

#endif