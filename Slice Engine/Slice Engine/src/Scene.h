#ifndef SLICE_SCENE_H
#define SLICE_SCENE_H

#include <filesystem>
#include <string>
#include <fstream>
#include <chrono>


namespace SliceEngine
{
	struct Entity;

	struct Scene
	{
		std::string m_Name;
		std::filesystem::path m_FilePath;
		std::vector<Entity> m_Entities;
	};
}

#endif