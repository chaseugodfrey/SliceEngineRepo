#include "pch.h"
#include "Engine.h"
#include "ECS/ECSTypes.h"
#include "ECS/PhysicSystem.h"
#include "Physics/PhysicsDebug.h"

namespace SliceEngine
{

	void Engine::Init()
	{
		SLICE_LOG("Initializing Slice Engine.");
		glfwInit();
		window = Window::CreateWindow();

		// Set up Engine Systems
		isRunning = true;

		inputs = std::make_unique<InputSystem>();

		SLICE_LOG("Register default allocator for Jolt Function Pointer");
		//Jolt uses function pointers for memory allocation, sets up the function pointers Jolt uses internally.
		JPH::RegisterDefaultAllocator(); 

		SLICE_LOG("Hook Jolt Tracer to SliceEngine Logger");
		//Jolt has a global function pointer "Trace" for debugging and logging messages
		//Hook Jolt Trace into SliceEngine’s logger.
		JPH::Trace = JoltTraceImpl;

#ifdef EDITOR
		editor = std::make_unique<Editor>();
		editor->Init(window);
#endif


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
			glfwMakeContextCurrent(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Main Body
			inputs->Update(window);
			//

#ifdef EDITOR
			editor->Render(window);
#endif

			glfwSwapBuffers(window);
			/*glfwPollEvents();*/
			if (glfwWindowShouldClose(window))
				isRunning = false;
		}
	}

	void Engine::Exit()
	{
#ifdef EDITOR
		editor->Exit();
#endif
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}