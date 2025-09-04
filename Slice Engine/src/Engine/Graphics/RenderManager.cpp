#include "RenderManager.h"
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define PI05F 1.57079632679f

namespace SliceEngine
{
	RenderManager::RenderManager()
	{
		mWorldSpaceGraphics = std::make_unique<WorldSpaceGraphicsSystem>();

		cam.position = glm::vec3(2.f, 0.f, 0.f);
		cam.target = glm::vec3(1.f, 0.f, 0.f);
		cam.near = 0.5f;
		cam.far = 200.f;
		cam.pov = 60.f;
	}

	void RenderManager::Init(Registry& reg)
	{
		mWorldSpaceGraphics->Bind(reg);
	}

	void RenderManager::Render(GLFWwindow* window, ResourceManager* rcManager)
	{
		UpdateCamera(cam, window, 0.f, 0.f);
		cam.position.x -= 0.001f;
		cam.position.z += 0.002f;
		
		mWorldSpaceGraphics->UseShader(rcManager);
		UpdateRenderCam(cam, rcManager);
		
		mWorldSpaceGraphics->Render(window, rcManager);
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
	void RenderManager::UpdateRenderCam(Camera& camera, ResourceManager* rcManager)
	{
		GLint uniformLoc;
		uniformLoc = glGetUniformLocation(rcManager->GetShader().s, "V");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &camera.V[0][0]);
		uniformLoc = glGetUniformLocation(rcManager->GetShader().s, "P");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &camera.P[0][0]);
	}
}