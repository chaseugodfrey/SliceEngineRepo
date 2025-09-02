#include <pch.h>
#include "ContentBrowser.h"

namespace SliceEngine
{
	void ContentBrowser::Draw()
	{
		ImGui::Begin("Content Browser");
		//ImGuiID contentDock = ImGui::GetID("contentDock");
		//ImGui::DockSpace(contentDock, ImVec2(0, 0), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);

		ImGui::Text("Hierarchy Here");
		ImGui::Text("Hierarchy Here");
		ImGui::Text("Hierarchy Here");
		ImGui::Text("Hierarchy Here");
		ImGui::Text("Hierarchy Here");

		ImGui::End();
	}

}
