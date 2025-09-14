#include <pch.h>
#include "Editor.h"
#include "../Engine/Engine.h"

namespace SliceEngine
{
	Editor::Editor(Engine* r_engine) : engine(r_engine)
	{
	}

	void Editor::Init(GLFWwindow* window)
	{
		SLICE_LOG("Initializing Editor.");
		InitImGUI(window);
		InitEditorState();
		InitWindowManager(*editorState);
	}

	void Editor::Update()
	{
		editorState->renderManager = engine->mRender.get();
	}

	void Editor::Render(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// in order to toggle gameplay input on/off from editor UI w/o restarting
		// tell inputsystem whether imgui is capturing input this frame
		ImGuiIO& io = ImGui::GetIO();
		// this line is where editor tells inputsystem each frame whether imgui is using keyboard/mouse
		SliceEngine::InputSystem::Get().SetImGuiCapture(io.WantCaptureKeyboard, io.WantCaptureMouse); 

		// toolbar with a Play toggle
		ImGui::Begin("Toolbar");
		static bool s_PlayMode = false; // track play mode state
		if (ImGui::Checkbox("Play", &s_PlayMode)) // check if toggled
		{
			if (s_PlayMode) // if its play, enable game input
			{
				SliceEngine::InputSystem::Get().SetMode(SliceEngine::InputMode::Game);
				SliceEngine::InputSystem::Get().BindCallbacksToWindow(window);
			}
			else // else, keep input in editor mode and unbind callbacks, leaving it to imgui
			{
				SliceEngine::InputSystem::Get().UnbindCallbacks();
				SliceEngine::InputSystem::Get().SetMode(SliceEngine::InputMode::Editor);
			}
		}
		ImGui::End();


		windowManager->Render();
		
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Editor::Exit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	// Inits

	void Editor::InitImGUI(GLFWwindow* window)
	{
		SLICE_LOG("Checking ImGUI Version.");
		IMGUI_CHECKVERSION();

		SLICE_LOG("Creating ImGui Context.");
		SLICE_LOG_VALUES("ImGui Version: ", IMGUI_VERSION);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init("#version 450");
		// this line overrides the chain and can block the engine’s callbacks when you later enter Play, commented out for now
		//glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback); 
	}

	void Editor::InitEditorState()
	{
		SLICE_LOG("EDITOR: Initializing Session.");
		editorState = std::make_unique<EditorState>();
		editorState->Init();
	}

	void Editor::InitWindowManager(EditorState& editorState)
	{
		SLICE_LOG("EDITOR: Creating Window Manager.");
		windowManager = std::make_unique<WindowManager>();
		windowManager->Init(editorState);
	}



}