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
		inputs->Init(window);
		audio = std::make_unique<AudioManager>();
		mResource = std::make_unique<ResourceManager>();

		audio->Init();
		audio->LoadSound("BGMTest", "Assets/Audio/BGM_MainMenu_Mix1.wav", false, false);
		//audio->PlaySound("BGMTest", SliceEngine::SoundCategory::BGM, SliceEngine::AudioManager::InternalSound::SOUND_BGM, false, 0.5f);

		mResource->LoadShader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
		mResource->LoadModel("Assets/Models/Cube.txt");
		mRender = std::make_unique<RenderManager>();
		InitSystem(mWorldSpaceGraphics);
		mRender->InitAndLink(mWorldSpaceGraphics, window);

		InitSystem(mPhysicsTest);
		InitSystem(mTransform);


#ifdef EDITOR
		editor = std::make_unique<Editor>(this);
		editor->Init(window);
#endif
	}

	void Engine::Update()
	{
	
		//physics.Bind(mRegistry);

		entt::entity entity = mRegistry.create();
		mRegistry.emplace<Transform>(entity, glm::vec3(0.f), glm::vec3(50.f,0.f,0.f));
		mRegistry.emplace<RigidBody>(entity, false);
		mRegistry.emplace<Renderer>(entity);

		mPhysicsTest->Update(2.0f);
		//physics(2.0f);

		mRegistry.remove<RigidBody>(entity);

		while (isRunning)
		{
			glfwMakeContextCurrent(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Main Body
			inputs->Update();
			//

			mRender->Render(window, mResource.get());
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
		for (auto& system : mSystems)
		{
			system->Unbind();
		}

		audio->Exit();
#ifdef EDITOR
		editor->Exit();
#endif
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}