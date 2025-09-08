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
		struct FBODat
		{
			GLuint FBO;
			GLuint textureID{}, depthTex{};
		};
		
		RenderManager();
		~RenderManager();

		void InitAndLink(std::shared_ptr<WorldSpaceGraphicsSystem> wsgs, GLFWwindow* window);

		void Render(GLFWwindow* window, ResourceManager* rcManager);

		void LoadCam();
		void UpdateCamera(Camera& camera, GLFWwindow* window, float xOffset, float yOffset);
		void UpdateCamGPU(Camera& camera, ResourceManager* rcManager);
		
		void CreateFramebuffer(int width, int height);
		GLuint GetTexture();

		void IDPick(const int& mouseX, const int& mouseY);

		FBODat mScene;		// For drawing the scene onto a texture
		//GLuint pboIds[2];	// For Object Picking
		//GLuint pboIdx[2];
		unsigned int mIDHovered;

		std::shared_ptr<WorldSpaceGraphicsSystem> mWorldSpaceGraphics;
		Camera cam;
	};
}

#endif