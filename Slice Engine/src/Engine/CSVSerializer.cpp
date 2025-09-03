#include "CSVSerializer.h"

namespace SliceEngine
{
	namespace CSVSerializer
	{
        void Serialize(csv const& input, std::string const& path)
        {

        }

		csv Deserialize(std::string const& path)
		{
			std::ifstream ifs(path);

			csv result;

			if (!ifs.is_open())
			{
				Logger::LogError("CSVSerializer", "CSV File in " + path + " cannot be opened/found.");
				return result;
			}

			Logger::LogValue("CSVSerializer", "CSV File in " + path + " opened and read successfully.");

            std::string cur_line;
            std::vector<std::string> col_keys;

            //Column headers are the keys for the x axis
            if (std::getline(ifs, cur_line))
            {
                std::istringstream iss(cur_line);
                std::string word;

                bool first = true;
                while (std::getline(iss, word, ','))
                {
                    if (first)
                    {
                        //Skip top-left corner (empty cell)
                        first = false;
                        continue;
                    }
                    col_keys.push_back(word);
                }

                result.num_cols = static_cast<int>(col_keys.size());
            }

            //Remaining rows
            while (std::getline(ifs, cur_line))
            {
                std::istringstream iss(cur_line);
                std::string word;

                //First word in row = row key
                if (!std::getline(iss, word, ','))
                    continue;

                std::string row_key = word;
                int col_index = 0;

                //Remaining words = values
                while (std::getline(iss, word, ','))
                {
                    if (col_index < result.num_cols)
                    {
                        const std::string& col_key = col_keys[col_index];
                        result.data[row_key][col_key] = word;
                    }
                    col_index++;
                }

                result.num_rows++;
            }

            ifs.close();
            return result;
		}

		void Append(std::string const& path, std::string const& string_to_append)
		{
			std::ofstream file(path, std::ios::app);

			if (file.is_open())
			{
				file << string_to_append << "\n";
				file.close();
			}
			else
			{
				Logger::LogError("CSVSerializer", "CSV File in " + path + " cannot be opened/found.");
			}
		}

        void Print(csv const& input)
        {
            for (const auto& [row_key, row_map] : input.data)
            {
                Logger::Log("CSVSerializer::Print", row_key + ":");

                for (const auto& [col_key, value] : row_map)
                {
                    Logger::Log("CSVSerializer::Print", " " + col_key + " = " + value);
                }
            }
        }

		void Test()
		{			
            Print(Deserialize("Assets/Test.csv"));
		}
	}
}