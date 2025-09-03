#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ECSTypes.h"
#include <entt/entt.hpp>
#include "GOFactory.h"

class GameObject
{
public:
	friend class GOFactory;

	GameObject(Registry& reg) : mRegistry(reg)
	{
		mEntity = mRegistry.create();
	};

	~GameObject()
	{

	};

	template<typename T, typename... Args>
	T& AddComponent(Args&&... args)
	{
		return mRegistry.emplace<T>(mEntity, std::forward<Args>(args)...);	
	}

	template<typename T>
	void RemoveComponent()
	{
		mRegistry.remove<T>(mEntity);
	}

	template<typename T>
	bool HasComponent()
	{
		mRegistry.all_of<T>(mEntity);
	}
	
	template<typename T>
	T& GetComponent()
	{
		T* component = mRegistry.try_get<T>(mEntity);

		if (component)
		{
			return &component;

		}

		// NOTE: Throw error when component does not exist
		return T{};
	}

	Entity GetEntity()
	{
		return mEntity;
	}
	

private:
	Entity mEntity{};
	std::string mName;
	Registry& mRegistry;

};


#endif