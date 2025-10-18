#include "LoggerThread.h"
#include "DataBase.h"
#include <iostream>
#include <thread>


LoggerThread::LoggerThread(EventQueue& q, const std::string& dbFile)
  : worker(), 
    queue(q), 
    running(false), 
    logger(nullptr),
    database(dbFile), 
    currentLevel(0)
{
    std::cout << "[LoggerThread] The constructor is called, the database is created: " << dbFile << std::endl;
    logger = Logger::GetLogger(currentLevel, "events.log");
    std::cout << "[LoggerThread] The logger is initialized" << std::endl;
}

void LoggerThread::start() 
{
    running = true;
    std::cout << "LoggerThread started" << std::endl;
    worker = std::thread([this]() { this->run(); });
}

void LoggerThread::stop()
{
    running = false;
    queue.notifyAll();
    if (worker.joinable()) 
        worker.join();
}

void LoggerThread::setLogLevel(int newLevel) 
{
    std::lock_guard<std::mutex> lock(logMutex);
    currentLevel = newLevel;
    logger = Logger::GetLogger(currentLevel, "events.log");
    std::cout << "Logging level changed to " << currentLevel << std::endl;
}

void LoggerThread::run() 
{
    while (running) 
    {
        Event e;
        if (!queue.try_pop(e, running)) 
            break;

        std::lock_guard<std::mutex> lock(logMutex);
        logger->Write(e);
        database.insertEvent(e, currentLevel);
        eventCount++;
    }
    std::cout << "LoggerThread finished." << std::endl;
}