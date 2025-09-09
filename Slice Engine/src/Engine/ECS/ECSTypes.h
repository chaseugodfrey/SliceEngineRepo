#ifndef ECS_TYPES
#define ECS_TYPES

#include <entt/entt.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <xprop/xproperty.h>

using Entity = entt::entity;
using Registry = entt::registry;

namespace SliceEngine
{
	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		//XPROPERTY_DEF 
		//(
		//	"Transform", Transform, 
		//	xproperty::obj_member<"position", &Transform::position>,
		//	xproperty::obj_member<"rotation", &Transform::rotation>,
		//	xproperty::obj_member <"scale", &Transform::scale>
		//);

	//public: static auto PropertiesDefinition()
	//{
	//	assert(false);

	//	using namespace xproperty;
	//	return xproperty::def
	//}
	};

	//XPROPERTY_REG(Transform);

	struct Renderer
	{

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