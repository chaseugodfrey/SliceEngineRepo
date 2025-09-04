#include <pch.h>
#include "ResourceManager.h"
#include "WorldSpaceGraphicsSystem.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/euler_angles.hpp"

namespace SliceEngine
{
	void WorldSpaceGraphicsSystem::UseShader(ResourceManager* rcManager)
	{
		thisShader = rcManager->GetShader();
		glUseProgram(thisShader.s);
	}
	void WorldSpaceGraphicsSystem::Render(GLFWwindow* window, ResourceManager* rcManager)
	{
		glClearColor(0.75294f, 1.f, 0.93333f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Model& cube = rcManager->GetModel();
		glBindVertexArray(cube.vao);
		
		//operator()(1.f);
		Update(1.0f);
		glDrawArrays(cube.drawMode, 0, cube.drawCnt);
	}

	void WorldSpaceGraphicsSystem::EntityOnEnter(entt::registry& reg, entt::entity entity)
	{

	}

	void WorldSpaceGraphicsSystem::EntityOnExit(entt::registry& reg, entt::entity entity)
	{

	}

	void WorldSpaceGraphicsSystem::EntityOnUpdate(entt::registry& reg, entt::entity entity, float dt)
	{
		auto& transform = reg.get<Transform>(entity);

		glm::mat4x4 trans(1.f);
		glm::mat4x4 scale(1.f);
		glm::mat4x4 rot = glm::eulerAngleXYZ(transform.rotation.x, transform.rotation.y, transform.rotation.z);
		glm::scale(scale, transform.scale);
		glm::translate(trans, transform.position);

		glm::mat4x4 M{ trans * scale * rot };

		GLint uniformLoc;
		uniformLoc = glGetUniformLocation(thisShader.s, "M");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &M[0][0]);
	}

}