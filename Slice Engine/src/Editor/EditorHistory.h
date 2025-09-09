#ifndef EDITOR_HISTORY_H
#define EDITOR_HISTORY_H

namespace SliceEngine
{
	class EditorHistory
	{
	public:
		void Log();
		void Undo();
		void Redo();
	};
}

#endif
