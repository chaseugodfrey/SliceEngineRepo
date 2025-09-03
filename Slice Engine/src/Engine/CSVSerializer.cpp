#include "CSVSerializer.h"

namespace SliceEngine
{
	namespace CSVSerializer
	{
		Parsed_CSV_Row_Data* Parsed_CSV::Find_Row_With_ID(std::string const& _search_string, unsigned int _col)
		{
			for (Parsed_CSV_Row_Data m_pd : comma_seperated_data)
			{
				if (std::strcmp(m_pd.associated_data[_col].c_str(), _search_string.c_str()) == 0)
				{
					return &(comma_seperated_data[m_pd.row]);
				}
			}
			return nullptr;
		}

		Parsed_CSV Parse_CSV(std::string const& _path)
		{
			std::ifstream ifs(_path);

			Parsed_CSV p;
			Parsed_CSV_Row_Data pd;

			if (ifs.is_open())
			{
				Logger::LogValue("CSVSerializer", "CSV File in " + _path + " opened and read successfully.");

				std::string cur_line;
				std::string word;
				std::istringstream iss{};
				int cur_row{};

				std::getline(ifs, cur_line);
				p.num_rows++;
				p.num_cols = (int)(std::count(cur_line.begin(), cur_line.end(), ',')) + 1;
				iss = std::istringstream(cur_line);
				while (std::getline(iss, word, ','))
				{
					pd.row = cur_row;
					pd.associated_data.push_back(word);
				}

				p.comma_seperated_data.push_back(pd);
				pd.associated_data.clear();

				while (std::getline(ifs, cur_line))
				{
					cur_row++;
					iss = std::istringstream(cur_line);

					while (std::getline(iss, word, ','))
					{
						pd.row = cur_row;
						pd.associated_data.push_back(word);
					}

					p.comma_seperated_data.push_back(pd);
					pd.associated_data.clear();

					p.num_rows++;
				}
				ifs.close();
			}
			else
			{
				Logger::LogError("CSVSerializer", "CSV File in " + _path + " cannot be opened/found.");
				return p;
			}

			return p;
		}

		void Append_CSV(std::string const& _path, std::string const& _string_to_append)
		{
			std::ofstream file(_path, std::ios::app);

			if (file.is_open())
			{
				file << _string_to_append << "\n";
				file.close();
			}
			else
			{
				Logger::LogError("CSVSerializer", "CSV File in " + _path + " cannot be opened/found.");
			}
		}
	}
}