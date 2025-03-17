#ifndef SLICE_TEST_H
#define SLICE_TEST_H

#include <filesystem>

#include "Logger.h"
#include "Scene.h"
#include "SceneManager.h"


namespace SliceEngine
{
	Scene TestLoadSceneFile()
	{
		SLICE_LOG("Loading Scene File");

		Scene scene{};
		scene.m_Name = "My Scene";
		scene.m_FilePath = ASSET_DIR + scene.m_Name + ".scene";

		SceneManager sceneManager{};
		sceneManager.RetrieveScene(scene);
		
		return scene;
	}

	bool LoadSceneAsync()
	{
		std::thread thread(TestLoadSceneFile);
		SLICE_LOG("Loading Scene File");

		Scene scene{};
		scene.m_Name = "My Scene";
		scene.m_FilePath = ASSET_DIR + scene.m_Name + ".scene";
	}
}

#endif