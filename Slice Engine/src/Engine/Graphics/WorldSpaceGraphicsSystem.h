#ifndef WORLD_SPACE_GRAPHICS_MANAGER_H
#define WORLD_SPACE_GRAPHICS_MANAGER_H

#include "glfw/include/glfw3.h"
#include "ResourceManager.h"

namespace SliceEngine
{
	class WorldSpaceGraphicsSystem
	{
	public:
		void Render(GLFWwindow* window, ResourceManager* rcManager);
	};
}


#endif