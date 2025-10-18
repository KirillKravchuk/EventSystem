#pragma once

#include <chrono>
#include <string>


struct Event
{
	std::chrono::system_clock::time_point timestamp;
	int event_id = 0;
	int parameter_1 = 0;
	int parameter_2 = 0;
	int parameter_3 = 0;
	std::string note = "";
};