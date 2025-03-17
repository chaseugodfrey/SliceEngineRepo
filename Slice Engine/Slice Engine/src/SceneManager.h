#ifndef SLICE_SCENE_MANAGER_H
#define SLICE_SCENE_MANAGER_H

#include "Scene.h"
#include <vector>

namespace SliceEngine
{
	struct Entity
	{
		int id;
	};

	class SceneManager
	{
	public:
		// load scene from asset
		void RetrieveScene(Scene scene);
		void LoadScene(Scene scene);

		// can only be called 
		void UnloadScene();
		void LoadSceneAsync();

		// TESTING PURPOSES
		std::vector<Entity> entityList;
		void PrintCurrentScene();
	};
}

#endif