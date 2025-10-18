#include <iostream>
#include <thread>
#include <string>
#include <atomic>
#include <csignal>
#include "EventQueue.h"
#include "EventGenerator.h"
#include "LoggerThread.h"
#include "CommandHandler.h"
#include "DataBase.h"


std::atomic<bool> running{ true };

int main()
{
    std::cout << "Starting Event System" << std::endl << std::endl;

    EventQueue queue;
    LoggerThread loggerThread(queue, "events.db");
    EventGenerator generator(queue);
    CommandHandler commandHandler(loggerThread, generator);

    loggerThread.start();
    generator.start();

    std::cout << "System started. Available commands: date, time, level 0, level 1, level 2, faster, slower, pause, resume, stat, exit" << std::endl;

    std::string command;

    while (running) 
    {
        std::cout << "> ";

        if (std::getline(std::cin, command)) 
            commandHandler.handleCommand(command);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    generator.stop();
    loggerThread.stop();

    std::cout << "System stopped." << std::endl;

	return 0;
}