#ifndef ECS_TYPES
#define ECS_TYPES

#include <entt/entt.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/quaternion.hpp>
#include <xprop/xproperty.h>
#include <rttr/registration.h>

using Entity = entt::entity;
using Registry = entt::registry;

namespace SliceEngine
{
	struct testStruct
	{
		int val;
	};

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};

	//XPROPERTY_REG(Transform);

	struct Renderer
	{
		// May need to change if rendering pipeline is diff
		std::string model;
		std::string texture;
	};

	struct SceneGraph
	{
		//PLACEHOLDER to change to GUID or any unique identifier for gameobjects
		std::string parentID;
		std::vector<std::string> childrenID;

		//maybe no need
		//std::string leftID;
		//std::string rightID;
	};

	struct Camera
	{
		float pov, near, far;
		GLuint textureID{}, depthTex{};
	};

	RTTR_REGISTRATION
	{
	rttr::registration::class_<Transform>("Transform")
		.property("position", &Transform::position)
		.property("rotation", &Transform::rotation)
		.property("scale", &Transform::scale);
	rttr::registration::class_<Renderer>("Renderer")
		.property("model", &Renderer::model)
		.property("texture", &Renderer::texture);
	rttr::registration::class_<SceneGraph>("SceneGraph")
		.property("parentID", &SceneGraph::parentID)
		.property("childID", &SceneGraph::childrenID);
	}
}

#endif