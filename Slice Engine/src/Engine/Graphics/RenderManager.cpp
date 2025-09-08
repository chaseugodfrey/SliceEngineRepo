#include "RenderManager.h"
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define PI05F 1.57079632679f

namespace SliceEngine
{
	RenderManager::RenderManager(){	}
	RenderManager::~RenderManager()
	{
		glDeleteTextures(1, &mScene.textureID);
		//glDeleteTextures(1, &mScene.picker_id);
		glDeleteTextures(1, &mScene.depthTex);
		glDeleteFramebuffers(1, &mScene.FBO);
		//glDeleteBuffers(2, pboIds);
	}
	void RenderManager::InitAndLink(std::shared_ptr<WorldSpaceGraphicsSystem> wsgs, GLFWwindow* window)
	{
		mWorldSpaceGraphics = wsgs;

		LoadCam();

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		CreateFramebuffer(width, height);
	}

	void RenderManager::Render(GLFWwindow* window, ResourceManager* rcManager)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 1);
		//IDPick(mousePosX, mousePosY);

		UpdateCamera(cam, window, 0.f, 0.f);
		cam.position.x -= 0.001f;
		cam.position.z += 0.002f;
		
		mWorldSpaceGraphics->UseShader(rcManager);
		UpdateCamGPU(cam, rcManager);
		
		mWorldSpaceGraphics->Render(window, rcManager);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//std::swap(pboIdx[0], pboIdx[1]);
	}

	void RenderManager::LoadCam()
	{
		cam.position = glm::vec3(2.f, 0.f, 0.f);
		cam.target = glm::vec3(1.f, 0.f, 0.f);
		cam.near = 0.5f;
		cam.far = 200.f;
		cam.pov = 60.f;
	}
	void RenderManager::UpdateCamera(Camera& camera, GLFWwindow* window, float xOffset, float yOffset)
	{
		const float r = glm::sqrt(
			(camera.target.x - camera.position.x) * (camera.target.x - camera.position.x) +
			(camera.target.y - camera.position.y) * (camera.target.y - camera.position.y) +
			(camera.target.z - camera.position.z) * (camera.target.z - camera.position.z));
		float alpha = glm::asin((camera.target.y - camera.position.y) / r);
		float betta = std::atan2f((camera.target.x - camera.position.x), (camera.target.z - camera.position.z));

		// Adjust angles based on cursor offset
		if (yOffset < 0.0)
			alpha += -0.02f;
		else if (yOffset > 0.0)
			alpha += 0.02f;

		if (xOffset < 0.0)
			betta += -0.05f;
		else if (xOffset > 0.0)
			betta += 0.05f;

		// Clamp vertical angle
		alpha = glm::clamp(alpha, -PI05F + 0.01f, PI05F - 0.01f);

		// Update target based on spherical coordinates
		camera.target.x = camera.position.x + r * glm::cos(alpha) * glm::sin(betta);
		camera.target.y = camera.position.y + r * glm::sin(alpha);
		camera.target.z = camera.position.z + r * glm::cos(alpha) * glm::cos(betta);

		camera.V = glm::lookAt(camera.position, camera.target, glm::vec3{ 0.f,1.f,0.f });

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		camera.P = glm::perspective(glm::radians(camera.pov), static_cast<float>(width) / static_cast<float>(height), camera.near, camera.far);
	}
	void RenderManager::UpdateCamGPU(Camera& camera, ResourceManager* rcManager)
	{
		GLint uniformLoc;
		uniformLoc = glGetUniformLocation(rcManager->GetShader().s, "V");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &camera.V[0][0]);
		uniformLoc = glGetUniformLocation(rcManager->GetShader().s, "P");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &camera.P[0][0]);
	}

	void RenderManager::CreateFramebuffer(int width, int height)
	{
		glGenFramebuffers(1, &mScene.FBO);
		glBindFramebuffer(GL_FRAMEBUFFER, mScene.FBO);

		glCreateTextures(GL_TEXTURE_2D, 1, &mScene.textureID);
		glTextureStorage2D(mScene.textureID, 1, GL_RGBA16F, width, height);
		glTextureParameterf(mScene.textureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameterf(mScene.textureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mScene.textureID, 0); // GL_COLOR_ATTACHMENT0 - First Out

		//glCreateTextures(GL_TEXTURE_2D, 1, &mScene.picker_id);
		//glTextureStorage2D(mScene.picker_id, 1, GL_R32UI, width, height);
		//glTextureParameterf(mScene.picker_id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		//glTextureParameterf(mScene.picker_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, mScene.picker_id, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &mScene.depthTex);
		glTextureStorage2D(mScene.depthTex, 1, GL_DEPTH_COMPONENT32F, width, height);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mScene.depthTex, 0);

		//glGenRenderbuffers(1, &mScenes[i].RBO);
		//glBindRenderbuffer(GL_RENDERBUFFER, mScenes[i].RBO);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mScenes[i].RBO);

		unsigned int drawBuffers[] = {
			GL_COLOR_ATTACHMENT0
			//,GL_COLOR_ATTACHMENT1
		};
		glDrawBuffers(sizeof(drawBuffers) / sizeof(unsigned int), drawBuffers);


		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			SLICE_LOG_WARNING("Framebuffer not complete");
		}

		//glGenBuffers(2, pboIds);
		//glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[0]);
		//glBufferData(GL_PIXEL_PACK_BUFFER, 4, 0, GL_STREAM_READ);
		//glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[1]);
		//glBufferData(GL_PIXEL_PACK_BUFFER, 4, 0, GL_STREAM_READ);
		//pboIdx[0] = 0;
		//pboIdx[1] = 1;


		//glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
		//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
	GLuint RenderManager::GetTexture()
	{
		return mScene.textureID;
	}

	void RenderManager::IDPick(const int& mouseX, const int& mouseY)
	{
		//// if out of bounds
		//if (mouseX > 1920 || mouseX < 0 || mouseY > 1080 || mouseY < 0)
		//{
		//	mIDHovered = std::numeric_limits<unsigned int>().max();
		//	return;
		//}

		//GLint prevBinding{};
		//glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prevBinding);

		//glBindFramebuffer(GL_FRAMEBUFFER, mScene.FBO);
		//glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[pboIdx[0]]);

		//glNamedFramebufferReadBuffer(mScene.FBO, GL_COLOR_ATTACHMENT1);
		//glReadPixels(mouseX, mouseY, 1, 1,
		//	GL_RED_INTEGER, GL_UNSIGNED_INT, 0);

		//glBindBuffer(GL_PIXEL_PACK_BUFFER, pboIds[pboIdx[1]]);
		//GLuint* src = (GLuint*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
		//if (src)
		//{
		//	mIDHovered = *src;
		//	glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		//}
		////if (RenderHelper::GetInstance()->mEditorWindowActive)
		////	RenderHelper::GetInstance()->mSelectedID = goID;
		//if (mIDHovered >= std::numeric_limits<unsigned int>().max())
		//	mIDHovered = 0;

		//glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
		//glReadBuffer(GL_NONE);
		//glBindFramebuffer(GL_FRAMEBUFFER, prevBinding);
		//return;
	}

}