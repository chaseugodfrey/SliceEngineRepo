#include "pch.h"
#include "Engine.h"
#include "../ECS/ECSTypes.h"
#include "../ECS/PhysicSystem.h"

namespace SliceEngine
{
	void Engine::Init()
	{
		SLICE_LOG("Initializing Slice Engine.");
		glfwInit();
		window = Window::CreateWindow();
	}

	void Engine::Update()
	{
		Registry reg;

		PhysicSystem physics;
		physics.Bind(reg);

		entt::entity entity = reg.create();
		reg.emplace<Transform>(entity, 0.5f);
		reg.emplace<RigidBody>(entity, false);

		physics(2.0f);

		reg.remove<RigidBody>(entity);

		while (1)
		{
			glfwPollEvents();
			glfwWindowShouldClose(window);
		}
	}

	void Engine::Exit()
	{
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}