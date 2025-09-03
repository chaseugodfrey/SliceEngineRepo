#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "ECSTypes.h"
#include <entt/entt.hpp>
//q#include "GOFactory.h"

namespace SliceEngine
{
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

		void SetName(std::string name);

		std::string GetName();

		void Destroy();

		Entity GetEntity();

	private:
		Entity mEntity{};
		std::string mName;
		Registry& mRegistry;

	};

}


#endif