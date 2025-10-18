#include "utils.h"

std::string getFormattedDate(const std::chrono::system_clock::time_point& timestamp)
{
	auto time_t = std::chrono::system_clock::to_time_t(timestamp);
	std::tm tm_info;

#ifdef _WIN32
		localtime_s(&tm_info, &time_t);
#else
		localtime_r(&time_t, &tm_info);
#endif
	std::stringstream ss;
	ss << std::put_time(&tm_info, "%Y-%m-%d");
	return ss.str();
}

std::string getFormattedTime(const std::chrono::system_clock::time_point& timestamp)
{
	auto time_t = std::chrono::system_clock::to_time_t(timestamp);
	std::tm tm_info;

#ifdef _WIN32
		localtime_s(&tm_info, &time_t);
#else
		localtime_r(&time_t, &tm_info);
#endif

	std::stringstream ss;
	ss << std::put_time(&tm_info, "%H:%M:%S");
	return ss.str();
}

std::string getFormattedDateTime(const std::chrono::system_clock::time_point& timestamp) 
{ return getFormattedDate(timestamp) + " " + getFormattedTime(timestamp); }