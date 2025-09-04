#include <pch.h>
#include "EW_ContentBrowser.h"

namespace SliceEngine
{

	ContentBrowser::ContentBrowser(EditorState& editorState) : editorState(editorState)
	{
		editorState.CreateDirectory(*editorState.contentBrowserState->root);
	}

	void ContentBrowser::Draw()
	{
		ImGui::Begin("Content Browser");
		//ImGuiID contentDock = ImGui::GetID("contentDock");
		//ImGui::DockSpace(contentDock, ImVec2(0, 0), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);

		if (ImGui::Button("Reload"))
		{
			editorState.ResetRootDirectory();
			editorState.CreateDirectory(*editorState.contentBrowserState->root);
		}

		/*Setting the ItemSpacing Style to 0, 0 for the 2 child windows*/
		ImGuiStyle& style = ImGui::GetStyle();
		//SLICE_LOG("Style Padding:" + std::to_string(style.ItemSpacing.x) + " " + std::to_string(style.ItemSpacing.y));
		style.ItemSpacing = ImVec2(0, 0);

		/*Asset Directory*/
		ImVec2 left_region = ImVec2(ImGui::GetContentRegionAvail().x * 0.25f, ImGui::GetContentRegionAvail().y);

		if (ImGui::BeginChild("##dir", left_region, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX))
		{

			DisplayFolders(*editorState.contentBrowserState->root);
			//ImGui::Text("Directory Here!");

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

	void ContentBrowser::DisplayFolders(DirectoryNode& node)
	{

		if (node.path.empty())
		{
			ImGui::Text("No Path Found!");
			return;
		}
		else
		{
			if (ImGui::TreeNodeEx(node.fileName.c_str()))
			{
				for (auto& entry : node.children)
				{
					//ImGui::Indent();
					DisplayFolders(entry);
					//ImGui::Unindent();
				}
				ImGui::TreePop();
			}
			
		}
	}

}
