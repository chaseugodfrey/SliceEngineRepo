#include "../Slice_pch.h"
#include "SceneManager.h"

namespace SliceEngine
{
	void SceneManager::RetrieveScene(Scene scene)
	{
		SLICE_LOG("Attempting to retrieve scene: " + scene.m_FilePath.string());

		std::fstream sceneFile{ scene.m_FilePath };

		if (sceneFile.fail())
			return SLICE_LOG("Scene File does not exist.");

		if (sceneFile.is_open())
		{
			SLICE_LOG(scene.m_FilePath.string());

			int id{};
			while (sceneFile >> id)
			{
				scene.m_Entities.push_back(Entity{ id });
			}
		}

		sceneFile.close();
	}

	void SceneManager::LoadScene(Scene scene)
	{
		entityList.clear();
		for (size_t i = 0; i < scene.m_Entities.size(); i++)
		{
			entityList.push_back(scene.m_Entities[i]);
		}

		PrintCurrentScene();
	}

	void SceneManager::PrintCurrentScene()
	{
		std::string msg{};
		msg += "Displaying Scene List:\n";
		for (Entity& entity : entityList)
		{
			msg += "Entity ID: ";
			msg += std::to_string(entity.id) + "\n";
		}

		SLICE_LOG(msg);
	}
}