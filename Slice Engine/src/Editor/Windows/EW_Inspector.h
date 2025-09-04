#ifndef EDITOR_INSPECTOR_H
#define EDITOR_INSPECTOR_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class Inspector : public EditorWindow
	{
	public:
		void Draw() override final;
	};
}

#endif