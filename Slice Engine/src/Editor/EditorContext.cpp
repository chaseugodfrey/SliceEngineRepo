#include "EditorContext.h"
#include "../Engine/ECS/GOFactory.h"

namespace SliceEngine
{
	EditorContext::EditorContext(GOFactory& factory) : goFactory(factory)
	{

	}

	void EditorContext::AddGameObject()
	{
		goFactory.CreateGO();
	}
}
