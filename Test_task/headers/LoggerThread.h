#pragma once

#include <atomic>
#include <thread>
#include <memory>
#include "EventQueue.h"
#include "Logger.h"
#include "DataBase.h"


class CommandHandler;

class LoggerThread
{
public:
    LoggerThread(EventQueue& q, const std::string& dbFile);
    void start();
    void stop();
    void setLogLevel(int newLevel);
    int getEventCount() const { return eventCount.load(); }
private:
    void run();
    std::thread worker;
    EventQueue& queue;
    std::atomic<bool> running;
    std::unique_ptr<Logger> logger;
    DataBase database;
    std::mutex logMutex;
    int currentLevel;
    std::atomic<int> eventCount{0};
};

