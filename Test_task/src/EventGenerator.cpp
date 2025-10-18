#include "EventGenerator.h"
#include "EventQueue.h"
#include "utils.h"
#include <iostream>
#include <chrono>
#include <thread>


EventGenerator::EventGenerator(EventQueue& q) :
	running(false),
	worker(),
	queue(q),
	randomGenerator(std::random_device{}()),
	event_id(100, 999),
	parameter_1(1000, 9999),
	parameter_2(1000, 9999),
	parameter_3(1000, 9999),
	minDelayMs(1000),
	maxDelayMs(4000)
	{
	}

std::string EventGenerator::generateNote()
{
	int template_dist = std::uniform_int_distribution<int>(0, static_cast<int>(event_templates.size()) - 1)(randomGenerator);
	return event_templates[template_dist];
}

Event EventGenerator::generateEvent()
{
	Event e
	{
		std::chrono::system_clock::now(),
		event_id(randomGenerator),
		parameter_1(randomGenerator),
		parameter_2(randomGenerator),
		parameter_3(randomGenerator),
		generateNote()
	};

	queue.push(e);
	return e;
}

void EventGenerator::run()
{
	std::uniform_int_distribution<int> delayDist;
	while (running)
	{
		if (paused)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			continue;
		}

		generateEvent();

		int minDelay, maxDelay;
		{
			std::lock_guard<std::mutex> lock(delayMutex);
			minDelay = minDelayMs;
			maxDelay = maxDelayMs;
		}

		delayDist = std::uniform_int_distribution<int>(minDelay, maxDelay);
		int delay = delayDist(randomGenerator);
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	std::cout << "EventGenerator finished." << std::endl;
}

void EventGenerator::start()
{
	if (running) return;
	running = true;
	std::cout << "EventGenerator started" << std::endl;
	worker = std::thread(&EventGenerator::run, this);
	std::cout << "EventGenerator started (" << minDelayMs << "–" << maxDelayMs << " ms)\n";
}

void EventGenerator::stop()
{
	running = false;
	if (worker.joinable()) worker.join();
	std::cout << "EventGenerator stopped\n";
}

void EventGenerator::faster()
{
	std::lock_guard<std::mutex> lock(delayMutex);
	minDelayMs = std::max(200, minDelayMs - 500);
	maxDelayMs = std::max(500, maxDelayMs - 2000);
	std::cout << "Faster! New delay range: " << minDelayMs << "-" << maxDelayMs << " ms" << std::endl;
}

void EventGenerator::slower()
{
	std::lock_guard<std::mutex> lock(delayMutex);
	minDelayMs += 500;
	maxDelayMs += 2000;
	std::cout << "Slower! New delay range: " << minDelayMs << "-" << maxDelayMs << " ms" << std::endl;
}

void EventGenerator::pause()
{
	paused = true;
	std::cout << "Event generation paused\n";
}

void EventGenerator::resume()
{
	if (paused)
	{
		paused = false;
		std::cout << "Event generation resumed\n";
	}
	else
		std::cout << "Event generation is already running\n";
}