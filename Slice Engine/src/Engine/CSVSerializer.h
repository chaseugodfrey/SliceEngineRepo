#ifndef CSVSERIALIZER_H
#define CSVSERIALIZER_H

#include "Logger.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

namespace SliceEngine
{
	namespace CSVSerializer
	{
		struct csv
		{
			int num_rows{};
			int num_cols{};

			//for preserving original order for serialization after it was scrambled in the map for fast accessing speed
			std::vector<std::string> row_keys;
			std::vector<std::string> col_keys;

			std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
		};

		void Serialize(csv const& input, std::string const& path);

		csv Deserialize(std::string const& path);

		void Append(std::string const& path, std::string const& string_to_append);

		//Debug
		void Print(csv const& input);

		//Uses Assets/Test.csv in deserializing it and 
		void Test();
	}
}

#endif