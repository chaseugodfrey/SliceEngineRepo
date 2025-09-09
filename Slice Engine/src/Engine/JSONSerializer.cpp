#include "JSONSerializer.h"

namespace SliceEngine
{
	namespace JSONSerializer
	{
		//Save json (the data structure) to JSON (the file) Note: This replaces the file in the filepath with data in the given json
		void Serialize(json const& input, std::filesystem::path const& filePath)
		{
			std::ofstream ofs(filePath);
			if (!ofs.is_open())
			{
				Logger::LogError("JSONSerializer::Serialize", "Unable to write JSON to path: " + filePath.string());
				return;
			}
			ofs << input;
			ofs.close();
		}

		json RecursiveSerialize(GameObject& node)
		{
			json output;				

			//rttr::instance = 
			//rttr::type t = component.get_type();
			//output["type"] = t.get_name().to_string();

			//for (auto& prop : t.get_properties())
			//{
			//	rttr::variant value = prop.get_value(component);
			//	output[][prop.get_name().to_string()]
			//}

			//for (auto& meth : t.get_methods())
			//{
			//	output[meth.get_name().to_string()] =
			//}

			// Handle children recursively
			//if (!node.children.empty())
			//{
			//	output["children"] = json::array();
			//	for (auto const& child : node.children)
			//	{
			//		output["children"].push_back(RecursiveSerialize(child));
			//	}
			//}

			return output;
		}

		//Loads JSON (the file) and returns it as a json (the data structure) that can be accessed and edited
		json Deserialize(std::filesystem::path const& filePath)
		{
			std::ifstream ifs(filePath);
			if (!ifs.is_open())
			{
				Logger::LogError("JSONSerializer::Deserialize", "Unable to find/load JSON in path: " + filePath.string());
				return json{};
			}

			json output;
			ifs >> output;
			return output;
		}

		GameObject RecursiveDeserialize(json const& input)
		{
			//GameObject node;

			////Examples
			//if (input.contains("transform"))
			//{
			//	//Assign transforms
			//}


			//node.name = input.at("name").get<std::string>();
			//node.value = input.at("value").get<int>();

			//if (input.contains("children"))
			//{
			//	for (const auto& child_json : input["children"])
			//	{
			//		node.children.push_back(DeserializeNode(child_json)); // recursion!
			//	}
			//}

			return GameObject(Registry());
		}

		static void TestSerialize()
		{
			json test;

			std::string root("Scene");
			int num_objects_in_test_scene{ 10 };

			//add a number stored as double
			test["Examples"]["pi"] = 3.141;

			//add a Boolean stored as bool
			test["Examples"]["happy"] = true;

			//add a string stored as std::string
			test["Examples"]["name"] = "Niels";

			//add another null object by passing nullptr
			test["Examples"]["nothing"] = nullptr;

			//add an object inside the object
			test["Examples"]["answer"]["everything"] = 42;

			//add an array stored as std::vector (using an initializer list)
			test["Examples"]["list"] = { 1, 0, 2 };

			//add another object (using an initializer list of pairs)
			test["Examples"]["object"] = { {"currency", "SGD"}, {"value", 42.99} };

			for (int i{}; i < num_objects_in_test_scene; ++i)
			{
				test[root][i]["Sorting_Order"] = i;
				test[root][i]["Transform"]["Position"] = { 1.0f, 2.0f, 3.0f };
				test[root][i]["Transform"]["Rotation"] = { 1.0f, 2.0f, 3.0f };
				test[root][i]["Transform"]["Scale"] = { 1.0f, 2.0f, 3.0f };
			}

			Serialize(test, "Testing/Temporary/TestSerialize.scene");
		}

		static void TestDeserialize()
		{
			json test = Deserialize("Testing/Temporary/TestSerialize.scene");
			if (test != json{})
			{
				Logger::LogValue("JSONSerializer::Test", "JSON Serialization and Deserialization succeeded with no errors and result is in Testing/Temporary/TestSerialize.scene.");
			}
		}

		void Test()
		{
			JSONSerializer::TestSerialize();
			JSONSerializer::TestDeserialize();
		}

		std::vector<rttr::instance> make_instances_from_entity(entt::registry& registry, entt::entity entity)
		{
			std::vector<rttr::instance> result;

			//if (registry.all_of<Transform>(entity))
			//{
			//	result.emplace_back(registry.get<Transform>(entity));
			//}
			//if (registry.all_of<)

			return result;
		}
	}
}