#pragma once

#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "Event.h"


class EventQueue
{
public: 
	void push(const Event& event);
	Event pop();
	bool empty();
	size_t size();
	bool try_pop(Event& event, std::atomic<bool>& running);
	void notifyAll();

private:
	std::queue<Event> queue;
	std::mutex mutex;
	std::condition_variable condition;
};

