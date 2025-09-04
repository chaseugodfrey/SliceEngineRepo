#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <memory>
#include "WorldSpaceGraphicsSystem.h"
#include "../ECS/ECSTypes.h"

namespace SliceEngine
{
	class RenderManager
	{
	public:
		RenderManager();
		void Init(Registry& reg);


		void Render(GLFWwindow* window, ResourceManager* rcManager);
		void UpdateCamera(Camera& camera, GLFWwindow* window, float xOffset, float yOffset);
		void UpdateRenderCam(Camera& camera, ResourceManager* rcManager);

		std::unique_ptr<WorldSpaceGraphicsSystem> mWorldSpaceGraphics;
		Camera cam;
	};
}

#endif