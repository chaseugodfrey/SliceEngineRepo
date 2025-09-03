#include <pch.h>
#include "ContentBrowser.h"

namespace SliceEngine
{

	//ContentBrowser::ContentBrowser(EditorState& editorState) : contentBrowser(editorState->contentBrowserState)
	//{ }

	void ContentBrowser::Draw()
	{
		ImGui::Begin("Content Browser");

		if (ImGui::Button("Reload"))
		{

		}

		/*Setting the ItemSpacing Style to 0, 0 for the 2 child windows*/
		ImGuiStyle& style = ImGui::GetStyle();
		//SLICE_LOG("Style Padding:" + std::to_string(style.ItemSpacing.x) + " " + std::to_string(style.ItemSpacing.y));
		style.ItemSpacing = ImVec2(0, 0);

		/*Asset Directory*/
		ImVec2 left_region = ImVec2(ImGui::GetContentRegionAvail().x * 0.25f, ImGui::GetContentRegionAvail().y);

		if (ImGui::BeginChild("##dir", left_region, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX))
		{
			ImGui::Text("Directory Here!");

			ImGui::EndChild();
		}

		ImGui::SameLine();

		/*Folder Directory*/
		ImVec2 right_region = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);
		if (ImGui::BeginChild("##folder", right_region, ImGuiChildFlags_Border))
		{
			ImGui::Text("Folder Stuff Here!");

			ImGui::EndChild();
		}

		ImGui::End();
	}

}
