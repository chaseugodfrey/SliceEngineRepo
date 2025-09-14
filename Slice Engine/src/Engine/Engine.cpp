#include "pch.h"
#include "Engine.h"
#include "ECS/ECSTypes.h"
#include "ECS/PhysicSystem.h"
#include "Window.h"
#include "Core.h"

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

		Core::GetInstance()->InitSystem<SoundSystem>();
		Core::GetInstance()->InitSystem<WorldSpaceGraphicsSystem>();
		Core::GetInstance()->InitSystem<TransformSystem>();

		//InitSystem<SoundSystem>();
		audio->Init();
		//audio->LoadSound("BGMTest", "Assets/Audio/BGM/BGM_MainMenu_Mix1.wav", false);
		audio->LoadSound("Test3D", "Assets/Audio/BGM/3DAudioTest.wav", true);
		audio->PlaySound("Test3D", SliceEngine::SoundCategory::BGM, SliceEngine::AudioManager::InternalSound::SOUND_BGM,true, false, 0.5f);

		mResource->LoadShader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
		mResource->LoadModel("Assets/Models/Cube.txt");
		mRender = std::make_unique<RenderManager>();
		//InitSystem<WorldSpaceGraphicsSystem>();
		//mRender->InitAndLink(Core::GetInstance()->GetSystem<WorldSpaceGraphicsSystem>(), window);
		Core::GetInstance()->InitSystem<CameraSystem>();

		mRender->InitAndLink(window);

		//InitSystem(mPhysicsTest);
		//InitSystem<TransformSystem>();

		framerateManager = std::make_unique<FramerateManager>();
		framerateManager->Init();


#ifdef EDITOR
		editor = std::make_unique<Editor>(this);
		editor->Init(window);
#endif
	}

	void Engine::Update()
	{
	
		//physics.Bind(mRegistry);

		auto& entity = Core::GetInstance()->mFactory.CreateGO();
		//Core::GetInstance()->mRegistry.emplace<Transform>(entity, glm::vec3(0.f), glm::vec3(50.f,0.f,0.f));
		//Core::GetInstance()->mRegistry.emplace<RigidBody>(entity, false);
		//Core::GetInstance()->mRegistry.emplace<Renderer>(entity);

		//entity.AddComponent<Transform>(glm::vec3(0.f), glm::vec3(50.f, 0.f, 0.f));
		entity.AddComponent<RigidBody>(false);
		entity.GetComponent<Transform>().position = glm::vec3(0.f);
		entity.GetComponent<Transform>().rotation = glm::vec3(50.f, 0.f, 0.f);

		entity.AddComponent<Renderer>();

		Core::GetInstance()->mFactory.TestLoop();

		//auto& test = Core::GetInstance()->mRegistry.get<Transform>(entity.GetEntity());
		//mPhysicsTest->Update(2.0f);
		//physics(2.0f);

		entity.RemoveComponent<RigidBody>();
		//Core::GetInstance()->mRegistry.remove<RigidBody>(entity);
		audio->SetSound3DPosition("Test3D", entity.GetComponent<Transform>().position);
		

		while (isRunning)
		{
			glfwMakeContextCurrent(window);
			glfwPollEvents();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Main Body
			framerateManager->StartFrame();

			framerateManager->StartSystem("Input");

			inputs->Update();



			framerateManager->EndSystem("Input");

			framerateManager->EndFrame();

			
			//
			auto& camTransform = mRender->GetMainCameraTransform();
			
			float moveSpeed = 0.001f;
			static int direction = 1; // 1 = right, -1 = left

			camTransform.position.z += moveSpeed * direction;

			if (camTransform.position.z > 1.5f) direction = -1; // reverse left
			if (camTransform.position.z < -1.5f) direction = 1;  // reverse right


			glm::vec3 forward = { -1.0f,0.0f,0.0f };

			glm::vec3 up = { 0.0f, 1.0f, 0.0f }; // if your engine uses Y-up
			

			
			glm::vec3 velVec = { 0.0f, 0.0f, 1.0f };
			

			
			audio->SetListenerAttributes(camTransform.position, velVec, forward, up);
			//audio->Update();
			mRender->Render(window, mResource.get());



#ifdef EDITOR
			editor->Update();
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
		Core::GetInstance()->UnbindSystems();
		audio->Exit();
#ifdef EDITOR
		editor->Exit();
#endif
		Window::CloseWindow(window);
		SLICE_LOG("Shutting Down Slice Engine.");
	}
}