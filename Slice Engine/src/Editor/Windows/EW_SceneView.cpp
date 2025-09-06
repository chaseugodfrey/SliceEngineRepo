#include <pch.h>
#include "EW_SceneView.h"
#include "../EditorState.h"

namespace SliceEngine
{
	SceneView::SceneView(EditorState& editorState) : editorState(editorState)
	{
	}

	void SceneView::Draw()
	{
		ImGui::Begin("Scene");

		auto size = ImGui::GetContentRegionAvail();
		ImVec2 pos = ImGui::GetCursorScreenPos();

		ImGui::GetWindowDrawList()->AddImage(
			(void*)editorState.sceneID, // Placeholder texture ID
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + ImGui::GetContentRegionAvail().x, pos.y + ImGui::GetContentRegionAvail().y),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		ImGui::End();
	}

}
