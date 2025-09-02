#include <pch.h>
#include "ContentBrowser.h"

namespace SliceEngine
{
	void ContentBrowser::Draw()
	{
		ImGui::Begin("Content Browser");

		ImGui::BeginChild("Hierarchy",ImVec2(200,150));
		ImGui::Text("Hierarchy Here");
		ImGui::EndChild();

		ImGui::BeginChild("Current Folder", ImVec2(300,300));
		ImGui::Text("Current Folder");
		ImGui::EndChild();

		ImGui::End();
	}

}
