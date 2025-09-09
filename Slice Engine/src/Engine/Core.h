#ifndef CORE_H
#define CORE_H
#include "Input/InputSystem.h"
#include "AudioManager.h"
#include "TransformSystem.h"
#include "Graphics/ResourceManager.h"
#include "Graphics/RenderManager.h"
#include "ECS/BaseSystem.h"
#include "ECS/PhysicSystem.h"
#include "Singleton.h"

namespace SliceEngine
{
	class Core : public Singleton<Core>
	{
	public:
		// TODO: Update retrieving the name to use RTTR's 
		// need to create window system that stores the window handle

		template<typename T>
		void InitSystem()
		{
			std::shared_ptr<T> system = std::make_shared<T>();
			system->Bind(mRegistry);

			//std::string systemName = rttr::type::get<T>().get_name().to_string();
			std::string systemName = typeid(T).name();

			mSystems[systemName] = system;
			//mSystems.push_back(system);
		}

		template <typename T>
		std::unique_ptr<T> GetSystem()
		{
			//std::string systemName = rttr::type::get<T>().get_name().to_string();
			std::string systemName = typeid(T).name();
			auto it = mSystems.find(systemName);
			if (it != mSystems.end())
			{
				return std::dynamic_pointer_cast<T>(it->second);
			}

			return nullptr;
		}
	
		void UnbindSystems();

		Registry mRegistry;

	private:
		std::unordered_map<std::string, std::unique_ptr<IBaseSystem>> mSystems;



	};


}

#endif

