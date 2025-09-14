#include "pch.h"
#include "Engine.h"
#include "ECS/ECSTypes.h"
#include "ECS/PhysicSystem.h"
#include "Window.h"
#include "Core.h"
#include "src/Engine/Input/InputAction.h"

namespace SliceEngine
{

	void Engine::Init()
	{
		SLICE_LOG("Initializing Slice Engine.");
		glfwInit();
		window = Window::CreateWindow();

		// Set up Engine Systems
		isRunning = true;

		//inputs = std::make_unique<InputSystem>();
		//inputs->Init(window);
		//inputs->SetEnabled(true); // enable input system
		//inputs->SetMode(SliceEngine::InputMode::Editor); 
		// set to editor mode so that editor owns input unless play mode is toggled
		// default to Editor mode on boot, create a “Gameplay” action map, and poll actions each frame

		// use singleton instead
		auto& input = SliceEngine::InputSystem::Get();
		input.Init(window);
		input.SetEnabled(true);
		input.SetMode(SliceEngine::InputMode::Editor);

		audio = std::make_unique<AudioManager>();
		mResource = std::make_unique<ResourceManager>();

		Core::GetInstance()->InitSystem<SoundSystem>();
		Core::GetInstance()->InitSystem<WorldSpaceGraphicsSystem>();
		Core::GetInstance()->InitSystem<TransformSystem>();

		//InitSystem<SoundSystem>();
		audio->Init();
		audio->LoadSound("BGMTest", "Assets/Audio/BGM_MainMenu_Mix1.wav", false, false);
		//audio->PlaySound("BGMTest", SliceEngine::SoundCategory::BGM, SliceEngine::AudioManager::InternalSound::SOUND_BGM, false, 0.5f);

		mResource->LoadShader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
		mResource->LoadModel("Assets/Models/Cube.txt");
		mRender = std::make_unique<RenderManager>();
		//InitSystem<WorldSpaceGraphicsSystem>();
		//mRender->InitAndLink(Core::GetInstance()->GetSystem<WorldSpaceGraphicsSystem>(), window);
		Core::GetInstance()->InitSystem<CameraSystem>();

		mRender->InitAndLink(window);

		/* 
		this block of code is used to test whether binding input actions work
		if my code is done correctly, i should be able to toggle play mode in editor and have input printed to console
		once i toggle play mode off, input should no longer be printed to console 
		*/
		using namespace SliceEngine;
		auto& IA = InputActions::Get();
		auto& gameplay = IA.CreateMap("Gameplay");

		// sample bindings
		gameplay.AddBinding("jump", Binding::Key(GLFW_KEY_SPACE));            // Space
		gameplay.AddBinding("shoot", Binding::Mouse(GLFW_MOUSE_BUTTON_LEFT)); // LMB [left mouse button]
		gameplay.AddBinding("dash", Binding::Key(GLFW_KEY_LEFT_SHIFT));       // L-Shift

		IA.SetActiveMap("Gameplay");


		//InitSystem(mPhysicsTest);
		//InitSystem<TransformSystem>();


#ifdef EDITOR
		editor = std::make_unique<Editor>(this);
		editor->Init(window);
#endif
	}

	void Engine::Update()
	{
	
		//physics.Bind(mRegistry);

		entt::entity entity = Core::GetInstance()->mRegistry.create();
		Core::GetInstance()->mRegistry.emplace<Transform>(entity, glm::vec3(0.f), glm::vec3(50.f,0.f,0.f));
		Core::GetInstance()->mRegistry.emplace<RigidBody>(entity, false);
		Core::GetInstance()->mRegistry.emplace<Renderer>(entity);

		//mPhysicsTest->Update(2.0f);
		//physics(2.0f);

		Core::GetInstance()->mRegistry.remove<RigidBody>(entity);

		while (isRunning)
		{
			glfwMakeContextCurrent(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Main Body
			//inputs->Update();
			SliceEngine::InputActions::Get().Update();

			// tests
			if (SliceEngine::InputActions::Get().GetActionPressed("jump"))
				SLICE_LOG("Jump (pressed)");

			if (SliceEngine::InputActions::Get().GetActionDown("shoot"))
				SLICE_LOG("Shooting (held)");

			if (SliceEngine::InputActions::Get().GetActionReleased("dash"))
				SLICE_LOG("Dash (released)");


			mRender->Render(window, mResource.get());
#ifdef EDITOR
			editor->Update();
			editor->Render(window);
#endif

			glfwSwapBuffers(window);
			/*glfwPollEvents();*/
			if (glfwWindowShouldClose(window))
				isRunning = false;

			// make sure keep mouse delta logic consistent
			// instead of using unique pointer, use singleton? because why? idek
			SliceEngine::InputSystem::Get().UpdatePrevInput();
		}
	}

	void Engine::Exit()
	{
		Core::GetInstance()->UnbindSystems();
		audio->Exit();
#ifdef EDITOR
		editor->Exit();
#endif
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}