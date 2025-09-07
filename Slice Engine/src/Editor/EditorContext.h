#ifndef EDITOR_CONTEXT_H
#define EDITOR_CONTEXT_H

namespace SliceEngine
{
	class GOFactory;
	class EditorContext
	{
	public:
		GOFactory& goFactory;

		EditorContext(GOFactory& factory);

		void AddGameObject();
	};
}


#endif