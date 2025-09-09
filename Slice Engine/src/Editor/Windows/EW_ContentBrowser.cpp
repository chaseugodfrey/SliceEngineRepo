#include <pch.h>
#include "EW_ContentBrowser.h"
#include "../EditorState.h"

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

		//ImGui::SameLine();

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
				
				DisplayItems(*editorState.selectedFolder);
				ImGui::EndChild();
			}
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

			if (std::none_of(node.children.begin(), node.children.end(), [](const DirectoryNode& child) 
				{return child.isDirectory; }))
			{
				flags |= ImGuiTreeNodeFlags_Leaf;
			}

			if (ImGui::TreeNodeEx(node.fileName.c_str(),flags))
			{
				if (ImGui::IsItemHovered() && ImGui::IsItemClicked(ImGuiMouseButton_Left))
				{
					SelectFile(node);
				}

				for (auto& entry : node.children)
				{
					DisplayFolders(entry);
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

					if (ImGui::ButtonEx(entry.path.filename().string().c_str(), ImVec2(0,0), ImGuiButtonFlags_None))
					{
						selectedEntry = &entry;
					}
					if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
					{
						selectedEntry = &entry;
						ImGui::OpenPopup("##RenameFile"); //It should open 
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						SelectFile(entry);
						return;
					}
				}
			}

			for (auto& entry : node.children)
			{
				if (!entry.isDirectory)
				{
					ImGui::TableNextColumn();


					if (ImGui::ButtonEx(entry.path.filename().string().c_str(),ImVec2(0,0), ImGuiButtonFlags_None))
					{
						selectedEntry = &entry;
					}

					if (ImGui::BeginPopupContextItem("##ItemEditPopup"))
					{
						selectedEntry = &entry;

						if (ImGui::MenuItem("Rename File"))
						{
							editorState.contentBrowserState->openRenameFile = true;
						}
						ImGui::EndPopup();
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right))
					{
						selectedEntry = &entry;
						ImGui::OpenPopup("##RenameFile"); //It should open 
					}

					if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
					{
						editorState.OpenFile();
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
		static char newName[256] = {};
		
		
		if (ImGui::BeginPopupModal("##RenameFile"))
		{
			if (ImGui::IsWindowAppearing()) //First-time copying the name of the file for ImGui to register it
			{
				std::memset(newName, 0, sizeof(newName));
				std::strncpy(newName, entry.fileName.c_str(), sizeof(newName) - 1);
				newName[sizeof(newName) - 1] = '\0';
			}
			ImGui::Text("New Filename : ");
			ImGui::SameLine();
			ImGui::InputText("##New Filename:", newName, sizeof(newName));

			if (ImGui::Button("Rename"))
			{
				if (newName[0] != '\0')
				{
					editorState.RenameFile(entry, newName);
					ImGui::CloseCurrentPopup();
				}
				else
				{
					SLICE_LOG_ERROR("Trying to rename into an empty filename!");
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
