#include "Logger.h"
#include "LoggerLevel0.h"
#include "LoggerLevel1.h"
#include "LoggerLevel2.h"
#include "Event.h"


std::mutex Logger::fileMutex;

Logger::Logger(const std::string& fileName) : fileName(fileName)
{
    file.open(fileName, std::ios::app);
    if (!file.is_open()) 
        std::cerr << "Error: Failed to open log file: " << fileName << std::endl;
    else
        std::cout << "The log file is open: " << fileName << std::endl;
}

Logger::~Logger() 
{
    if (file.is_open())
        file.close();
}

std::unique_ptr<Logger> Logger::GetLogger(int level, const std::string& fileName) 
{
    switch (level) 
    {
    case 0: return std::make_unique<LoggerLevel0>(fileName);
    case 1: return std::make_unique<LoggerLevel1>(fileName);
    case 2: return std::make_unique<LoggerLevel2>(fileName);
    default: return std::make_unique<LoggerLevel0>(fileName);
    }
}