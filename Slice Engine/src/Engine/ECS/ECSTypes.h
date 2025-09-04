#ifndef ECS_TYPES
#define ECS_TYPES

#include <entt/entt.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
using Entity = entt::entity;
using Registry = entt::registry;

namespace SliceEngine
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
	struct Renderer
	{
		// May need to change if rendering pipeline is diff
		std::string model;
		std::string texture;
	};
	struct Camera
	{
		glm::vec3 position;
		glm::vec3 target;
		glm::mat4 V;
		glm::mat4 P;
		float pov, near, far;
	};
}

#endif