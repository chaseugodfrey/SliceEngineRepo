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
		//ImGuiStyle& style = ImGui::GetStyle();
		//SLICE_LOG("Style Padding:" + std::to_string(style.ItemSpacing.x) + " " + std::to_string(style.ItemSpacing.y));
		//style.ItemSpacing = ImVec2(0, 0);

		/*Asset Directory*/
		ImVec2 left_region = ImVec2(ImGui::GetContentRegionAvail().x * 0.2f, ImGui::GetContentRegionAvail().y);

		if (left_region.x < 0 || left_region.y < 0)
		{
			left_region = ImVec2(0, 0);
		}

		if(left_region.x > 0 && left_region.y > 0)
		{
			if (ImGui::BeginChild("##dir", left_region, ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX))
			{

				DisplayFolders(*editorState.contentBrowserState->root);
				//ImGui::Text("Directory Here!");

				ImGui::EndChild();
			}
		}

		ImGui::SameLine();

		/*Folder Directory*/
		ImVec2 right_region = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y);

		if (right_region.x < 0 || right_region.y < 0)
		{
			right_region = ImVec2(0, 0);
		}

		if(right_region.x > 0 && right_region.y > 0)
		{
			if (ImGui::BeginChild("##folder", right_region, ImGuiChildFlags_Border))
			{
				if (editorState.selectedFolder != nullptr)
				{
					DisplayItems(*editorState.selectedFolder);
				}
				else
				{
					ImGui::Text("No selected Folder!");
				}

				ImGui::EndChild();
			}
		}

		//style.ItemSpacing = ImVec2(8, 4);

		SLICE_LOG("Left Region Coordinates: " + std::to_string(left_region.x) + " , " + std::to_string(left_region.y));
		SLICE_LOG("Right Region Coordinates: " + std::to_string(right_region.x) + " , " + std::to_string(right_region.y));

		if(editorState.selectedFolder != nullptr)
		{
			SLICE_LOG(editorState.selectedFolder->path.string());
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

		if (!node.isDirectory)
		{
			return;
		}

		else
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;

			if (node.children.empty())
			{
				flags |= ImGuiTreeNodeFlags_Leaf;
			}

			if (ImGui::TreeNodeEx(node.fileName.c_str(),flags))
			{
				if (ImGui::IsItemClicked(ImGuiMouseButton_Left))
				{
					SelectFile(node);
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
		static DirectoryNode* selectedEntry = nullptr;

		if (ImGui::BeginTable("##FolderDirectory", 5))
		{
			for (auto& entry : node.children)
			{
				if (entry.isDirectory)
				{
					ImGui::TableNextColumn();
					if (ImGui::ButtonEx(entry.path.filename().string().c_str(), ImVec2(0, 0), ImGuiButtonFlags_None))
					{
						selectedEntry = &entry;
						ImGui::OpenPopup("##RenameFile");
					}
				}
			}

			for (auto& entry : node.children)
			{
				if (!entry.isDirectory)
				{
					ImGui::TableNextColumn();
					if (ImGui::ButtonEx(entry.path.filename().string().c_str(), ImVec2(0, 0), ImGuiButtonFlags_None))
					{
						selectedEntry = &entry;
						ImGui::OpenPopup("##RenameFile");
					}
				}
			}

			if (selectedEntry != nullptr)
			{
				RenameFilePopup(*selectedEntry);
			}

			ImGui::EndTable();
		}
	}

	void ContentBrowser::SelectFile(DirectoryNode& node)
	{
		editorState.selectedFolder = &node;
	}

	void ContentBrowser::RenameFilePopup(DirectoryNode& entry)
	{
		char newName[256] = "\0";
		if (ImGui::BeginPopupModal("##RenameFile"))
		{

			ImGui::Text(entry.path.string().c_str());
			ImGui::InputText("New Name:", newName, sizeof(newName));

			if (ImGui::Button("Rename"))
			{
				if (newName[0] = '\0')
				{
					std::filesystem::path newPath = entry.path.parent_path() / newName;
					std::filesystem::directory_entry actualEntry = std::filesystem::directory_entry(entry.path);
					try
					{
						std::filesystem::rename(entry.path, newPath);
						actualEntry = std::filesystem::directory_entry(newPath);
						ImGui::CloseCurrentPopup();
					}
					catch (const std::exception& e)
					{
						ImGui::Text("Failed!", e.what());
					}
				}
				else
				{
					ImGui::Text("Please provide a valid name.");
				}
			}

			ImGui::SameLine();

			if (ImGui::Button("Cancel"))
			{
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

}
