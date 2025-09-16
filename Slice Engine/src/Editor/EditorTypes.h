#ifndef EDITOR_TYPES_H
#define EDITOR_TYPES_H

#include <filesystem>
#include <map>

namespace SliceEngine
{

	struct DirectoryNode
	{
		std::string fileName;
		bool isDirectory = false;
		std::filesystem::path path;
		DirectoryNode* parent = nullptr;
		std::map<std::string, DirectoryNode> children;
	};

}

#endif