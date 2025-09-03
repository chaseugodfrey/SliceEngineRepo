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

			//preserving original order for serialization if/when serialization is needed
			//std::vector<std::string> row_keys;
			//std::vector<std::string> col_keys;

			std::unordered_map<std::string, std::unordered_map<std::string, std::string>> data;
		};

		//NOT DOING IF NOT NEEDED: Alot of work so I'll ask designers if serialization is even needed or just need to load csv data and use it rather than edit and save it back into readable csv
		void Serialize(csv const& input, std::string const& path);

		csv Deserialize(std::string const& path);

		void Append(std::string const& path, std::string const& string_to_append);

		//Debug
		void Print(csv const& input);

		//Uses Testing/Units.csv in deserializing it and 
		void Test();
	}
}

#endif