#include <pch.h>
#include "Editor.h"

namespace SliceEngine
{
	void Editor::Init(GLFWwindow* window)
	{
		SLICE_LOG("Initializing Editor.");
		SLICE_LOG("Checking ImGUI Version.");
		IMGUI_CHECKVERSION();

		SLICE_LOG("Creating ImGui Context.");
		SLICE_LOG_VALUES("ImGui Version: ", IMGUI_VERSION);
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         

		//// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init("#version 450");
		glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
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

		//Render();
		RenderMainMenuBar();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Editor::Exit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Editor::RenderMainMenuBar()
	{
		ImGui::BeginMainMenuBar();
		ImGui::Text("A");
		ImGui::EndMainMenuBar();
	}
}