#include "BaseSystem.h"
#include "Engine/AudioManager.h"
#include <iostream>
#include <string>
// for testing purpose



struct SoundFile
{
	std::string filePath;
	float currentVolume;
	bool isLoop;
};

// for keeping track of entities that belong to sound system
struct SoundEntity {};

struct PhysicSystem : BaseSystem<SoundEntity, SoundFile>
{
	void EntityOnEnter(entt::registry& reg, entt::entity entity) override
	{
		std::cout << "Entity entering sound system" << std::endl;
	}

	void EntityOnExit(entt::registry& reg, entt::entity entity) override
	{
		std::cout << "Entity exiting sound system" << std::endl;
	}

	void EntityOnUpdate(entt::registry& reg, entt::entity entity, float dt) override
	{
		//auto& soundFile = reg.get<SoundFile>(entity);

		//std::cout << "Update Entity " << soundFile << std::endl;
	}
};