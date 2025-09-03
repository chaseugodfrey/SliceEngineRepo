#include "RenderManager.h"

namespace SliceEngine
{
	RenderManager::RenderManager()
	{
		mWorldSpaceGraphics = std::make_unique<WorldSpaceGraphicsSystem>();
	}

	void RenderManager::Render(GLFWwindow* window, ResourceManager* rcManager)
	{
		mWorldSpaceGraphics->Render(window, rcManager);
	}
}