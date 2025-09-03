#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include "../ThirdParty/nlohmann/include/json.hpp"
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <string>

using json = nlohmann::json;

namespace SliceEngine
{
	namespace JSONSerializer
	{
		void Serialize(json const& sceneJSON, std::string const& filePath);
		json Deserialize(std::string const& filePath);

		void Test();
	}	
}


#endif