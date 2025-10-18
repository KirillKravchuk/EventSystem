#include "CommandHandler.h"
#include "EventGenerator.h"
#include "LoggerThread.h"
#include <iostream>
#include <chrono>
#include <atomic>
#include "utils.h"


CommandHandler::CommandHandler(LoggerThread& loggerThread, EventGenerator& eventGenerator)
  : loggerThread(loggerThread), eventGenerator(eventGenerator)
{
	std::cout << "CommandHandler initialized" << std::endl;
	initializeCommands();
}

void CommandHandler::initializeCommands()
{
	commands.emplace("date", [this]() 
		{
			auto now = std::chrono::system_clock::now();
			std::cout << "Current date: " << getFormattedDate(now) << std::endl;
		});

	commands.emplace("time", [this]()
		{
			auto now = std::chrono::system_clock::now();
			std::cout << "Current time: " << getFormattedTime(now) << std::endl;
		});

	commands.emplace("level 0", [this]() { loggerThread.setLogLevel(0); });

	commands.emplace("level 1", [this]() { loggerThread.setLogLevel(1); });

	commands.emplace("level 2", [this]() { loggerThread.setLogLevel(2); });

	commands.emplace("faster", [this]() { eventGenerator.faster(); });
		
	commands.emplace("slower", [this]() { eventGenerator.slower(); });

	commands.emplace("pause", [this]() { eventGenerator.pause(); });

	commands.emplace("resume", [this]() { eventGenerator.resume(); });

	commands.emplace("stat", [this]()
		{
			std::cout << "Total events recorded (this session): " << loggerThread.getEventCount() << std::endl;
		});

	commands.emplace("exit", [this]()
		{
			std::cout << "Exit requested" << std::endl;
			extern std::atomic<bool> running;
			running = false;
		});
}

void CommandHandler::handleCommand(const std::string& command)
{
	auto it = commands.find(command);

	if (it != commands.end()) { it->second(); }
	else 
	{
		std::cout << "Unknown command: " << command << std::endl;
		std::cout << "Available commands: date, time, level 0, level 1, level 2, exit" << std::endl;
	}
}


