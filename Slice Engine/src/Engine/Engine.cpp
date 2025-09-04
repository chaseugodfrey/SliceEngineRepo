#include "pch.h"
#include "Engine.h"
#include "ECS/ECSTypes.h"
#include "ECS/PhysicSystem.h"
#include "Window.h"

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
		audio = std::make_unique<AudioManager>();

		audio->Init();
		audio->LoadSound("BGMTest", "Assets/Audio/BGM_MainMenu_Mix1.wav", false, false);
		audio->PlaySound("BGMTest", SliceEngine::SoundCategory::BGM, SliceEngine::AudioManager::InternalSound::SOUND_BGM, false, 0.5f);

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

		while (isRunning)
		{
			glfwMakeContextCurrent(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Main Body
			inputs->Update();
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
		audio->Exit();
#ifdef EDITOR
		editor->Exit();
#endif
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}