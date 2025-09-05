#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "../ThirdParty/nlohmann/include/json.hpp"
#include "Logger.h"
#include "../ECS/GameObject.h"
#include <iostream>
#include <fstream>
#include <string>

using json = nlohmann::json;

namespace SliceEngine
{
	//The workflow in my head
	//GameObject root = ...; // your scene root
	//json j = RecursiveSerialize(root);

	//// If you want to edit / validate / add metadata, do it here
	//j["metadata"] = "example";

	//Serialize(j, "scene.json");  // entomb it into a file

	namespace JSONSerializer
	{
		void Serialize(json const& input, std::string const& filePath);
		//GameObject in place of scenegraph node as placeholder
		json RecursiveSerialize(GameObject const& node);
		json Deserialize(std::string const& filePath);
		//GameObject in place of scenegraph node as placeholder
		GameObject RecursiveDeserialize(json const& input);

		void Test();
	}	
}


#endif