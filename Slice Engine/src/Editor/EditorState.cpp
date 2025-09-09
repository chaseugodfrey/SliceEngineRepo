#include <pch.h>
#include "EditorState.h"

namespace SliceEngine
{

	EditorState::EditorState() : contentBrowserState(std::make_unique<ContentBrowserState>()), selectedFolder(contentBrowserState->root.get())
	{}
	void EditorState::Init()
	{
		
		
	}

	void EditorState::RebuildDirectory(DirectoryNode& node)
	{
		ResetRootDirectory(node);
		CreateDirectory(node);
	}

	void EditorState::ResetRootDirectory(DirectoryNode& node)
	{
		node.children.clear();
	}

	void EditorState::CreateDirectory(DirectoryNode& node)
	{
		if (node.path.has_extension())
		{
			return;
		}

		for (const auto& entry : std::filesystem::directory_iterator(node.path))
		{
			node.children.emplace_back();
			DirectoryNode& child = node.children.back();
			child.path = entry.path();
			child.parent = &node;
			child.isDirectory = entry.is_directory();
			child.fileName = child.isDirectory ? entry.path().filename().string() : entry.path().stem().string();

			//node.children.push_back(child);


			CreateDirectory(child);

		}
		return;
	}

	void EditorState::RenameFile(DirectoryNode& entry, char* newName)
	{
		std::filesystem::path extension;
		std::filesystem::path newPath = entry.path.parent_path() / newName;
		if (entry.path.has_extension())
		{
			extension = entry.path.extension();
		}
		newPath += extension;
		std::filesystem::directory_entry actualEntry = std::filesystem::directory_entry(entry.path);
		try
		{

			std::filesystem::rename(entry.path, newPath);
			actualEntry = std::filesystem::directory_entry(newPath);
			entry.fileName = newName;
			entry.path = newPath;
		}
		catch (const std::exception& e)
		{
			ImGui::Text("Failed!", e.what());
		}
	}

	void EditorState::OpenFile()
	{
		SLICE_LOG("Open this file WIP!");
	}
}