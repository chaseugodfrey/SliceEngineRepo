#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <memory>
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "WorldSpaceGraphicsSystem.h"


namespace SliceEngine
{
	struct Cam
	{
		glm::vec3 position;
		glm::vec3 target;
		glm::mat4 V;
		glm::mat4 P;
	};

	class RenderManager
	{
	public:
		RenderManager();

		void Render(GLFWwindow* window, ResourceManager* rcManager);

		std::unique_ptr<WorldSpaceGraphicsSystem> mWorldSpaceGraphics;
	};
}

#endif