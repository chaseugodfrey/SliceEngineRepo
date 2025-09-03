#ifndef WORLD_SPACE_GRAPHICS_MANAGER_H
#define WORLD_SPACE_GRAPHICS_MANAGER_H

#include "glfw/include/glfw3.h"
#include "ResourceManager.h"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"

namespace SliceEngine
{
	struct Cam
	{
		glm::vec3 position;
		glm::vec3 target;
		glm::mat4 V;
		glm::mat4 P;
	};

	class WorldSpaceGraphicsManager
	{
	public:
		void Render(GLFWwindow* window, ResourceManager* rcManager);
	};
}


#endif