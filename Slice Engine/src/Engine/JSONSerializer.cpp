#include "JSONSerializer.h"

namespace SliceEngine
{
	namespace JSONSerializer
	{
		//Save json (the data structure) to JSON (the file)
		void Serialize(json const& JSON, std::string const& filePath)
		{
			std::ofstream ofs(filePath);
			if (!ofs.is_open())
			{
				Logger::LogError("JSONSerializer::Serialize", "Unable to write JSON to path: " + filePath);
				return;
			}
			ofs << JSON;
			ofs.close();
		}

		//Returns a json (the data structure) that can be accessed as if its a vector
		json Deserialize(std::string const& filePath)
		{
			std::ifstream ifs(filePath);
			if (!ifs.is_open())
			{
				Logger::LogError("JSONSerializer::Deserialize", "Unable to find/load JSON in path: " + filePath);
				return json{};
			}

			json SceneJSON;
			ifs >> SceneJSON;
			return SceneJSON;
		}

		static void TestSerialize()
		{
			json test;

			std::string root("Scene");
			int num_objects_in_test_scene{ 10 };

			// add a number stored as double (note the implicit conversion of j to an object)
			test["Examples"]["pi"] = 3.141;

			// add a Boolean stored as bool
			test["Examples"]["happy"] = true;

			// add a string stored as std::string
			test["Examples"]["name"] = "Niels";

			// add another null object by passing nullptr
			test["Examples"]["nothing"] = nullptr;

			// add an object inside the object
			test["Examples"]["answer"]["everything"] = 42;

			// add an array stored as std::vector (using an initializer list)
			test["Examples"]["list"] = { 1, 0, 2 };

			// add another object (using an initializer list of pairs)
			test["Examples"]["object"] = { {"currency", "SGD"}, {"value", 42.99} };

			/* Example output
			{
				"pi": 3.141,
				"happy": true,
				"name": "Niels",
				"nothing": null,
				"answer": {
				"everything": 42
				},
				"list": [1, 0, 2],
				"object": {
				"currency": "SGD",
				"value": 42.99
				}
			}
			*/

			for (int i{}; i < num_objects_in_test_scene; ++i)
			{
				test[root][i]["Sorting_Order"] = i;
				test[root][i]["Transform"]["Position"] = { 1.0f, 2.0f, 3.0f };
				test[root][i]["Transform"]["Rotation"] = { 1.0f, 2.0f, 3.0f };
				test[root][i]["Transform"]["Scale"] = { 1.0f, 2.0f, 3.0f };				
			}

			Serialize(test, "Assets/TestSerialize.scene");
		}

		static void TestDeserialize()
		{
			json test = Deserialize("Assets/TestSerialize.scene");			
			if (test != json{})
			{
				Logger::LogValue("JSONSerializer::Test", "JSON Serialization and Deserialization succeeded with no errors and result is in Assets/TestSerialize.scene.");
			}
		}

		//Creates a file called TestSerialize.scene to test serialization and deserialization with end result being in Assets/TestSerialize.scene
		void Test()
		{
			JSONSerializer::TestSerialize();
			JSONSerializer::TestDeserialize();
		}	
	}
}