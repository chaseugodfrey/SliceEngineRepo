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

		GameObject() = default;

		GameObject(Registry& reg) 
		{
			mRegistry = &reg;

			mEntity = mRegistry->create();
		};

		~GameObject()
		{

		};

		template<typename T, typename... Args>
		void AddComponent(Args&&... args)
		{
			rttr::type tType = rttr::type::get<T>();
			rttr::type transformType = rttr::type::get<Transform>();
			// Get UI transform here once we have it
			// then check if it already has transform dont add uitransform and vice versa
			
			mRegistry->emplace<T>(mEntity, std::forward<Args>(args)...);

			// idk why EnTT can't return a get<T>
			//return mRegistry->get<T>(mEntity);
		}

		template<typename T>
		void RemoveComponent()
		{
			rttr::type tType = rttr::type::get<T>();

			if (tType == rttr::type::get<Transform>())
			{
				// TODO_Gideon: log an error saying can't remove transform or smth

				return;
			}

			mRegistry->remove<T>(mEntity);
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
		std::string mName{};
		Registry* mRegistry{ nullptr };

	};

}


#endif