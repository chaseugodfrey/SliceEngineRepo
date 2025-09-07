#include <pch.h>
#include "EW_Hierarchy.h"

namespace SliceEngine
{
	Hierarchy::Hierarchy(EditorState& editorState)
	{
		for (int i = 0; i < 10; i++)
		{
			TreeNode a = { std::to_string(i) };
			nodes.push_back(a);
		}
	}

	void Hierarchy::Draw()
	{
		ImGui::Begin("Hierarchy");

		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1))
		{
			ImGui::OpenPopup("HierarchyContextMenu");
		}

		if (ImGui::BeginPopup("HierarchyContextMenu"))
		{
			if (ImGui::MenuItem("Create GameObject"))
			{
				TreeNode a = { "Empty GameObject" };
				nodes.push_back(a);
			}
			ImGui::EndPopup();
		}

		static int selected = -1;

		for (int i = 0; i < nodes.size(); i++)
		{
			if (ImGui::TreeNodeEx(nodes[i].name.c_str(), ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen))
			{
				if (ImGui::IsItemClicked())
					selected = i;
			}
		}

		ImGui::End();
	}

}
