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
			//editorState.ResetRootDirectory();
			editorState.RebuildDirectory(*editorState.contentBrowserState->root);
		}

		/*Setting the ItemSpacing Style to 0, 0 for the 2 child windows*/
		ImGuiStyle& style = ImGui::GetStyle();
		//SLICE_LOG("Style Padding:" + std::to_string(style.ItemSpacing.x) + " " + std::to_string(style.ItemSpacing.y));
		style.ItemSpacing = ImVec2(0, 0);

		/*Asset Directory*/
		ImVec2 left_region = ImVec2(ImGui::GetContentRegionAvail().x * 0.2f, ImGui::GetContentRegionAvail().y);

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
			if (editorState.selectedNode != nullptr)
			{
				DisplayItems(*editorState.selectedNode);
			}
			else
			{
				ImGui::Text("No selected Folder!");
			}

			ImGui::EndChild();
		}

		style.ItemSpacing = ImVec2(8, 4);

		if(editorState.selectedNode != nullptr)
		{
			SLICE_LOG(editorState.selectedNode->path.string().c_str());
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
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen;

			if (node.children.empty())
			{
				flags |= ImGuiTreeNodeFlags_Leaf;
			}

			if (ImGui::TreeNodeEx(node.fileName.c_str(),flags))
			{
				if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
				{
					editorState.selectedNode = &node;
				}

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

	void ContentBrowser::DisplayItems(DirectoryNode& node)
	{
		for (auto& entry : std::filesystem::directory_iterator(node.path))
		{
			if (entry.is_directory())
			{
				continue;
			}

			ImGui::Text(entry.path().filename().string().c_str());
		}
	}

}
