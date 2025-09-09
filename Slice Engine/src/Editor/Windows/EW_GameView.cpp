#include <pch.h>
#include "EW_GameView.h"
#include "../EditorState.h"
#include "../../Engine/Graphics/RenderManager.h"

namespace SliceEngine
{
	GameView::GameView(EditorState& editorState) : editorState(editorState)
	{
	}

	void GameView::Draw()
	{
		ImGui::Begin("Game");

		if (ImGui::BeginChild("##game_header", ImVec2(0, 30.0f), ImGuiChildFlags_None | ImGuiChildFlags_Borders, ImGuiWindowFlags_NoScrollbar))
		{
			ImGui::Text("Resolution");
			ImGui::SameLine();
			ImGui::SetNextItemWidth(150.0f);

			//if (ImGui::BeginCombo("##resolution_dropdown", resolutions[resolutionIndex].first))
			//{

			//	for (int n = 0; n < resolutions.size(); n++)
			//	{
			//		const bool is_selected = (resolutionIndex == n);
			//		if (ImGui::Selectable(resolutions[n].first, is_selected))
			//			resolutionIndex = n;

			//		// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
			//		if (is_selected)
			//			ImGui::SetItemDefaultFocus();
			//	}
			//	ImGui::EndCombo();
			//}

			ImGui::EndChild();

		}

		//if (resolutionIndex < 0 || resolutionIndex > resolutions.size())
		//	resolutionIndex = 0;

		const float src_width = 1920;
		const float src_height = 1080;

		float scene_width = ImGui::GetContentRegionAvail().x;
		float scene_height = ImGui::GetContentRegionAvail().y;

		float scale_x = scene_width / src_width;
		float scale_y = scene_height / src_height;

		float scale = std::min(scale_x, scale_y);

		float display_width = src_width * scale;
		float display_height = src_height * scale;

		ImVec2 pos = ImGui::GetCursorScreenPos();
		float offset_x = (scene_width - display_width) * 0.5f;
		float offset_y = (scene_height - display_height) * 0.5f;

		pos.x += offset_x;
		pos.y += offset_y;

		ImGui::GetWindowDrawList()->AddImage(
			(void*)editorState.renderManager->GetTexture(), // Placeholder texture ID
			pos,
			ImVec2(pos.x + display_width, pos.y + display_height),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);
		ImGui::End();
	}

}
