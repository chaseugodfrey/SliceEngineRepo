#include <pch.h>
#include "ContentBrowser.h"

namespace SliceEngine
{
	ContentBrowser::ContentBrowser(ContentBrowserState& m_state) : state(m_state) {}

	void ContentBrowser::Draw()
	{
		ImGui::Begin("Content Browser");

		if (ImGui::Button("Reload"))
		{

		}

		ImGui::End();
	}

}
