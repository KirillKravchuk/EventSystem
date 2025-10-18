#pragma once

#include <map>
#include <functional>
#include <string>
#include <memory>


class LoggerThread;

class EventGenerator;

// maybe it's better to use unordered_map 
class CommandHandler
{
private:
    LoggerThread& loggerThread;
    EventGenerator& eventGenerator;

    std::map<std::string, std::function<void()>> commands;

public:
    CommandHandler(LoggerThread& loggerThread, EventGenerator& eventGenerator);

    void handleCommand(const std::string& command);
    void initializeCommands();
};