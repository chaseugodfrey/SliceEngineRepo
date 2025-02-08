#ifndef SLICE_LOGGER_H
#define SLICE_LOGGER_H

#include "Common.h"

namespace SliceEngine
{
	template <typename T, typename = void>
	struct can_std_to_string : std::false_type {};

	template <typename T>
	struct can_std_to_string<T, std::void_t<decltype(std::to_string(std::declval<T>()))>> : std::true_type {};

	#define LOGGER_RESET   "\033[0m"
	#define LOGGER_RED     "\033[31m"
	#define LOGGER_GREEN   "\033[32m"
	#define LOGGER_YELLOW  "\033[33m"
	#define LOGGER_BLUE    "\033[34m"

	class Logger
	{
	public:

		enum class LogLevel
		{
			DEBUG, INFO, WARNING, ERROR, CRITICAL
		};

		template <typename T>
		static std::enable_if_t<can_std_to_string<T>::value, void>
		Log(T object, LogLevel level = LogLevel::DEBUG)
		{
			std::string log_level{};
			std::string log_color{};

			switch (level)
			{
			case LogLevel::DEBUG: log_level = "[DEBUG]    ";
				break;
			case LogLevel::INFO: log_level = "[INFO]     "; log_color = LOGGER_GREEN;
				break;
			case LogLevel::WARNING: log_level = "[WARNING]  "; log_color = LOGGER_YELLOW;
				break;
			case LogLevel::ERROR: log_level = "[ERROR]    "; log_color = LOGGER_BLUE;
				break;
			case LogLevel::CRITICAL:log_level = "[CRITICAL] "; log_color = LOGGER_RED;
				break;
			default:
				break;
			}

			auto now = std::chrono::system_clock::now();
			std::time_t time = std::chrono::system_clock::to_time_t(now);
			std::tm tm;
			localtime_s(&tm, &time);

			std::cout
				<< log_color
				<< log_level 
				<< std::put_time(&tm, "%Y-%m-%d %H:%M:%S :")
				<< std::to_string(object)
				<< LOGGER_RESET
				<< '\n';
		}
	};
}

#endif