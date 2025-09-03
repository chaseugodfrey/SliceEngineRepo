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

	void Editor::DrawMainMenu()
	{
		auto style = ImGui::GetStyle();
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 10.0f));
		ImGui::BeginMainMenuBar();
		
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Scene"))
			{
				
			}

			if (ImGui::MenuItem("Save Scene"))
			{

			}

			if (ImGui::MenuItem("Exit"))
			{

			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
		ImGui::PopStyleVar();

	}

	void Editor::DrawDockspace()
	{
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::Begin("Dockspace", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoMove);
		ImGuiID dockspace_id = ImGui::GetID("Dockspace");
		ImGui::DockSpace(dockspace_id, { 0,0 }, ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::End();

	}
}