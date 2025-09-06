#include "EditorConsole.h"

namespace SliceEngine
{
	void EditorConsole::Log(const std::string msg)
	{
		logMessages.push_back(msg);
	}

	void EditorConsole::Clear()
	{
		logMessages.clear();
	}
}