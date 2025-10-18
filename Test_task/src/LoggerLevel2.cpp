#include "LoggerLevel2.h"
#include "Event.h"
#include <iostream>
#include <iomanip>


LoggerLevel2::LoggerLevel2(const std::string& fileName)
    : Logger(fileName)
{
}

void LoggerLevel2::Write(const Event& e)
{
    std::lock_guard<std::mutex> lock(fileMutex);

    if (!file.is_open())
        return;

    file << "[" << getFormattedDateTime(e.timestamp) << "] "
        << "ID: " << e.event_id << " "
        << "P1 = " << e.parameter_1 << " "
        << "P2 = " << e.parameter_2 << " "
        << "P3 = " << e.parameter_3 << " "
        << "Note: " << e.note
        << std::endl;

    file.flush();
}