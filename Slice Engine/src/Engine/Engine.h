#ifndef ENGINE_H
#define ENGINE_H

#include "Window.h"
#include "Input/InputSystem.h"
#include "AudioManager.h"
#include "TransformSystem.h"
#include "Graphics/ResourceManager.h"
#include "Graphics/RenderManager.h"
#include "ECS/BaseSystem.h"
#include "ECS/PhysicSystem.h"
#include <rttr/registration.h>
#include <rttr/type.h>
#include "ECS/SliceRTTR.h"

#ifdef EDITOR
#include "../Editor/Editor.h"
#endif

namespace SliceEngine
{
	class Engine
	{
		GLFWwindow* window;
		bool isRunning;

#ifdef EDITOR
		std::unique_ptr<Editor> editor;
#endif
	public:
		// I'm testing a way to store all the systems in an array
		// to loop and unbind in exit
		// if it doesnt work down the line then just manually unbind all the systems instead.
		
		std::unordered_map<std::string, std::shared_ptr<IBaseSystem>> mSystems;

		//std::vector<std::shared_ptr<IBaseSystem>> mSystems;

		std::unique_ptr<InputSystem> inputs;
		std::unique_ptr<AudioManager> audio;
		//std::shared_ptr<TransformSystem> mTransform;
		std::unique_ptr<ResourceManager> mResource;
		std::unique_ptr<RenderManager> mRender;
		//std::shared_ptr<WorldSpaceGraphicsSystem> mWorldSpaceGraphics;
		//std::shared_ptr<PhysicSystem> mPhysicsTest;
		Registry mRegistry;

		void Init();

	
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
		std::shared_ptr<T> GetSystem()
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

		void Update();
		void Exit();

	};
}

#endif 