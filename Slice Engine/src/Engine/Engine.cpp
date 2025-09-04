#include "pch.h"
#include "Engine.h"
#include "ECS/ECSTypes.h"
#include "ECS/PhysicSystem.h"

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
		mResource = std::make_unique<ResourceManager>();
		mResource->LoadShader("Assets/basic.vert", "Assets/basic.frag");
		mResource->LoadModel("Assets/Cube.txt");
		mRender = std::make_unique<RenderManager>();


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
			mRender->Render(window, mResource.get());

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