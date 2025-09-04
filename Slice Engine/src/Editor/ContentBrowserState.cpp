#include "ContentBrowserState.h"

namespace SliceEngine
{
	void ContentBrowserState::CreateDirectory(DirectoryNode& node)
	{
		if(node.isDirectory)
		{
			for (const auto& entry : std::filesystem::directory_iterator(node.path))
			{


				auto child = std::make_unique<DirectoryNode>();
				child->path = entry.path();
				child->parent = &node;
				child->isDirectory = entry.is_directory();

				CreateDirectory(*child);

				node.children.push_back(std::move(child));
			}
		}
		else
		{
			return;
		}
	}
}