#include <pch.h>
#include "GameObject.h"

namespace SliceEngine
{
	void GameObject::SetName(std::string name)
	{
		mName = name;
	}

	std::string GameObject::GetName()
	{
		return mName;
	}

	void GameObject::Destroy()
	{
		mRegistry->destroy(mEntity);

		//mRegistry.eac
	}

	Entity GameObject::GetEntity()
	{
		return mEntity;
	}
}