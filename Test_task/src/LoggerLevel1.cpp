#include "LoggerLevel1.h"
#include "Event.h"
#include <iostream>
#include <iomanip>


LoggerLevel1::LoggerLevel1(const std::string& fileName)
    : Logger(fileName)
{
}

void LoggerLevel1::Write(const Event& e)
{
    std::lock_guard<std::mutex> lock(fileMutex);

    if (!file.is_open())
        return;

    file << "[" << getFormattedDateTime(e.timestamp) << "] "
        << "ID: " << e.event_id << " "
        << "P1 = " << e.parameter_1
        << std::endl;

    file.flush();
}