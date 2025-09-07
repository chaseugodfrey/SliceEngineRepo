#ifndef EDITOR_HIERARCHY_H
#define EDITOR_HIERARCHY_H

#include "../EditorWindow.h"

namespace SliceEngine
{
	class EditorState;

	struct TreeNode
	{
		std::string name;
	};

	class Hierarchy : public EditorWindow
	{
	public:

		std::vector<TreeNode> nodes;

		Hierarchy(EditorState& editorState);
		void Draw() override final;
	};
}

#endif