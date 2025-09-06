#ifndef EDITOR_CONSOLE_H
#define EDITOR_CONSOLE_H

namespace SliceEngine
{
	class EditorConsole
	{
		std::vector<std::string> logMessages;

	public:
		void Log(const std::string msg);
		void Clear();
	};
}

#endif