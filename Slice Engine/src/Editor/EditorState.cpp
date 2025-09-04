#include "EditorState.h"

namespace SliceEngine
{
	//void EditorState::RebuildDirectory()
	//{
	//	contentBrowserState->root = std::make_unique<DirectoryNode>();
	//	contentBrowserState->root->path = ASSET_DIR;

	//	std::queue<std::unique_ptr<DirectoryNode>> queue;
	//	queue.push(contentBrowserState->root.get());

	//	while (!queue.empty())
	//	{
	//		auto currentNode = queue.front();
	//		queue.pop();
	//		
	//		for (auto& entry : std::filesystem::directory_iterator(currentNode->path))
	//		{
	//			auto& node = std::make_unique<DirectoryNode>();
	//			node->path = entry;
	//			node->parent = currentNode;

	//			currentNode->children.push_back(node);

	//			if (entry.is_directory())
	//			{
	//				queue.push(*node);
	//			}
	//		}
	//	}

	//}

	void EditorState::Init()
	{
		contentBrowserState = std::make_unique<ContentBrowserState>();
		
	}
}