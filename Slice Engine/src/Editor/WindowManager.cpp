#include "WindowManager.h"

namespace SliceEngine
{
	void WindowManager::Init(EditorState& editorState)
	{
		AddWindow<ContentBrowser>(editorState);
		AddWindow<SceneView>(editorState);
		//AddWindow<GameView>(editorState);
		AddWindow<Hierarchy>(editorState);
		AddWindow<Inspector>(editorState);
		//AddWindow<Console>();
		//AddWindow<Animator>();
		//AddWindow<Profiler>();
		//AddWindow<Animation>();
	}

	void WindowManager::Render()
	{
		DrawMainMenu();
		DrawDockspace();
		
		for (auto& window : list)
		{
			window->Draw();
		}
	}

	void WindowManager::DrawMainMenu()
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

			ImGui::Separator();

			if (ImGui::MenuItem("Preferences"))
			{

			}

			if (ImGui::MenuItem("Exit"))
			{

			}

			ImGui::Separator();

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Animation"))
			{

			}

			if (ImGui::MenuItem("Animator"))
			{

			}

			if (ImGui::MenuItem("Console"))
			{

			}

			if (ImGui::MenuItem("Content Browser"))
			{

			}

			if (ImGui::MenuItem("Game"))
			{

			}

			if (ImGui::MenuItem("Hierachy"))
			{

			}

			if (ImGui::MenuItem("Inspector"))
			{

			}

			if (ImGui::MenuItem("Scene"))
			{

			}

			if (ImGui::MenuItem("Profiler"))
			{

			}

			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
		ImGui::PopStyleVar();

	}

	void WindowManager::DrawDockspace()
	{
		static bool firstTime = true;
		ImGuiViewport* viewport = ImGui::GetMainViewport();

		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		if(ImGui::Begin("Dockspace", 0, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse |
			ImGuiWindowFlags_NoMove))
		{
			ImGuiID dockspace_id = ImGui::GetID("Dockspace");
			ImGui::DockSpace(dockspace_id, ImVec2(0,0), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode);



			if (firstTime)
			{
				firstTime = false;

				ImGuiID dockMain = dockspace_id; // Main area
				ImGuiID dockBottom = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Down, 0.3f, nullptr, &dockMain);
				//ImGuiID dockBotLeft = ImGui::DockBuilderSplitNode(dockBottom, ImGuiDir_Left, 0.7f, nullptr, &dockBottom);
				//ImGuiID dockBotRight = dockBottom;
				ImGuiID dockLeft = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Left, 0.15f, nullptr, &dockMain);
				ImGuiID dockRight = ImGui::DockBuilderSplitNode(dockMain, ImGuiDir_Right, 0.3f, nullptr, &dockMain);

				//ImGui::DockBuilderDockWindow("FSM", dockBottom);
				ImGui::DockBuilderDockWindow("Scene", dockMain);
				ImGui::DockBuilderDockWindow("Content Browser", dockBottom);
				ImGui::DockBuilderDockWindow("Inspector", dockRight);
				ImGui::DockBuilderDockWindow("Hierarchy", dockLeft);
				//ImGui::DockBuilderDockWindow("Asset Browser", dockBottom);
				ImGui::DockBuilderFinish(dockMain);
			}
		}
		ImGui::End();

	}

}
