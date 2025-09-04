#include <pch.h>
#include "ResourceManager.h"
#include "WorldSpaceGraphicsSystem.h"
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/euler_angles.hpp"

namespace SliceEngine
{
	void WorldSpaceGraphicsSystem::UseShader(ResourceManager* rcManager)
	{
		mShader = rcManager->GetShader();
		glUseProgram(mShader.s);
	}
	void WorldSpaceGraphicsSystem::Render(GLFWwindow* window, ResourceManager* rcManager)
	{
		glClearColor(0.75294f, 1.f, 0.93333f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

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


		testParent = !testParent;

		glm::mat4x4 M(1.f);
		M = glm::scale(M, transform.scale);
		glm::mat4x4 Rot = glm::eulerAngleXYZ(glm::radians(transform.rotation.x), glm::radians(transform.rotation.y), glm::radians(transform.rotation.z));
		M *= Rot;
		M = glm::translate(M, transform.position);

		GLint uniformLoc;
		uniformLoc = glGetUniformLocation(mShader.s, "M");
		glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &M[0][0]);
	}

}