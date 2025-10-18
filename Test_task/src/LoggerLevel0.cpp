#include "LoggerLevel0.h"
#include "Event.h"
#include <iostream>
#include <iomanip>


LoggerLevel0::LoggerLevel0(const std::string& fileName)
    : Logger(fileName)
{
}

void LoggerLevel0::Write(const Event& e)
{
    std::lock_guard<std::mutex> lock(fileMutex);

    if (!file.is_open())
        return;

    file << "[" << getFormattedTime(e.timestamp) << "] "
        << "ID: " << e.event_id
        << std::endl;

    file.flush();
}
