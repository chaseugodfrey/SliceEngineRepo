#include <pch.h>
#include "ResourceManager.h"
#include "WorldSpaceGraphicsManager.h"

namespace SliceEngine
{
	void SliceEngine::WorldSpaceGraphicsManager::Render(GLFWwindow* window, ResourceManager* rcManager)
	{
		glClearColor(0.75294f, 1.f, 0.93333f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(rcManager->GetShader().s);
		//GLint uniformLoc;
		//uniformLoc = glGetUniformLocation(shaders.begin()->second.s, "V");
		//glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &camera.V[0][0]);
		//uniformLoc = glGetUniformLocation(shaders.begin()->second.s, "P");
		//glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, &camera.P[0][0]);

		Model& cube = rcManager->GetModel();
		glBindVertexArray(cube.vao);
		glDrawArrays(cube.drawMode, 0, cube.drawCnt);

	}

}