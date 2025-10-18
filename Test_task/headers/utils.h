#pragma once

#include <chrono>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>


std::string getFormattedDate(const std::chrono::system_clock::time_point& timestamp);

std::string getFormattedTime(const std::chrono::system_clock::time_point& timestamp);

std::string getFormattedDateTime(const std::chrono::system_clock::time_point& timestamp);