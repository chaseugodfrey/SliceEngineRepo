#include "pch.h"
#include "SliceEditor.h"

namespace SliceEngine
{

	void Editor::Init(GLFWwindow* window)
	{
		SLICE_LOG("Editor Initialized.");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		//// Setup Platform/Renderer backends
		ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
		ImGui_ImplOpenGL3_Init("#version 450");
		glfwSetKeyCallback(window, ImGui_ImplGlfw_KeyCallback);
	}

	void Editor::Update(GLFWwindow* window)
	{
		glfwMakeContextCurrent(window);
		ImGui_ImplGlfw_NewFrame();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		Render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	}

	void Editor::Render()
	{
		DisplayMainMenu();
	}

	void Editor::Exit()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void DoNothing()
	{

	}

	void Editor::DisplayMainMenu()
	{
		if (ImGui::BeginMainMenuBar())
		{

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Quit"))
				{
					SLICE_LOG("A");
				
				}

				if (ImGui::MenuItem("Some"))
				{

				}


				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Project"))
			{
				if (ImGui::MenuItem("AQuit"))
				{
					SLICE_LOG("B");

				}

				if (ImGui::MenuItem("ASome"))
				{

				}


				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}
	}


}