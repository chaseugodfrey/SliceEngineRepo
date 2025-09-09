#include <pch.h>
#include "EW_SceneView.h"
#include "../EditorState.h"
#include "../../Engine/Graphics/RenderManager.h"

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

		

		glm::vec3 move{};

		if (ImGui::IsKeyDown(ImGuiKey_W))
		{
			
		}

		if (ImGui::IsKeyDown(ImGuiKey_S))
		{
			
		}

		if (ImGui::IsKeyDown(ImGuiKey_A))
		{
			
		}

		if (ImGui::IsKeyDown(ImGuiKey_D))
		{
			
		}

		editorState.renderManager->cam.position += move;
		editorState.renderManager->cam.target += move;

		ImGui::GetWindowDrawList()->AddImage(
			(void*)editorState.renderManager->GetTexture(), // Placeholder texture ID
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + ImGui::GetContentRegionAvail().x, pos.y + ImGui::GetContentRegionAvail().y),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		ImGui::End();
	}

}
