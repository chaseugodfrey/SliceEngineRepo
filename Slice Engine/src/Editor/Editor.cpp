#include <pch.h>
#include "Editor.h"

namespace SliceEngine
{
	void Editor::Init(GLFWwindow* window)
	{
		SLICE_LOG("Initializing Editor.");
		InitImGUI(window);
		InitEditorState();
		InitWindowManager(*editorState);
	}

	void Editor::Update()
	{

	}

	void Editor::Render(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		DrawMainMenu();
		DrawDockspace();

#pragma region Test Dummy Windows
		/*ImGui::Begin("A");
		ImGui::Text("A");
		ImGui::End();

		ImGui::Begin("B");
		ImGui::Text("B");
		ImGui::End();*/
#pragma endregion

		//std::for_each(windowManager->list.begin(), windowManager->list.end(), [](auto& window) { window.draw(); });
		for (auto& window : windowManager->list)
		{
			window->Draw();
		}
		
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
		glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
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