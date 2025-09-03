#include "EditorInputs.h"

namespace SliceEngine
{
	void EditorInputs::Init()
	{
	}

	void EditorInputs::Update()
	{
		auto io = ImGui::GetIO();

		if (io.KeyCtrl)
		{
			if (ImGui::IsKeyPressed(ImGuiKey_Z))
			{

			}

			if (io.KeyShift && ImGui::IsKeyPressed(ImGuiKey_Z))
			{

			}

			if (ImGui::IsKeyPressed(ImGuiKey_Y))
			{

			}

			if (ImGui::IsKeyPressed(ImGuiKey_D))
			{

			}

			if (ImGui::IsKeyPressed(ImGuiKey_C))
			{

			}

			if (ImGui::IsKeyPressed(ImGuiKey_S))
			{

			}

			if (ImGui::IsKeyPressed(ImGuiKey_V))
			{

			}
		}
	}
}