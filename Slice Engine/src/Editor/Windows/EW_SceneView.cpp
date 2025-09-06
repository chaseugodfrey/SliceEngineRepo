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
		ImGui::GetWindowDrawList()->AddImage(
			(void*)editorState.sceneID, // Placeholder texture ID
			ImVec2{ ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y },
			ImVec2{ ImGui::GetCursorScreenPos().x + size.x, ImGui::GetCursorScreenPos().y + size.y },
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		ImGui::End();
	}

}
