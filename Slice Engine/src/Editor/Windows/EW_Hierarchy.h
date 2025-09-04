#ifndef EDITOR_HIERARCHY_H
#define EDITOR_HIERARCHY_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class Hierarchy : public EditorWindow
	{
	public:
		void Draw() override final;
	};
}

#endif