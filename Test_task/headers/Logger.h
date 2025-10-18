#pragma once

#include <iostream>
#include <fstream>
#include <mutex>
#include <memory>
#include <string>


struct Event;

class Logger
{
protected:
	std::ofstream file;
	std::string fileName;
	static std::mutex fileMutex;

	Logger(const std::string& fileName);
	
public:
	virtual ~Logger(); // UB if not virtual

	virtual void Write(const Event& e) = 0;

	static std::unique_ptr<Logger> GetLogger(int level, const std::string& fileName);
};

