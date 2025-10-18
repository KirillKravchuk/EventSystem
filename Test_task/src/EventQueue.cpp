#include "EventQueue.h"
#include <atomic>


void EventQueue::push(const Event& event)
{
    std::lock_guard<std::mutex> lock(mutex);
    queue.push(event);
    condition.notify_one();
}
 
Event EventQueue::pop() 
{
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [this] { return !queue.empty(); });

    Event event = queue.front();
    queue.pop();
    return event;
}

bool EventQueue::empty() 
{
    std::lock_guard<std::mutex> lock(mutex);
    return queue.empty();
}

size_t EventQueue::size() 
{
    std::lock_guard<std::mutex> lock(mutex);
    return queue.size();
}

void EventQueue::notifyAll() 
{
    std::lock_guard<std::mutex> lock(mutex);
    condition.notify_all();
}

bool EventQueue::try_pop(Event& event, std::atomic<bool>& running) 
{
    std::unique_lock<std::mutex> lock(mutex);
    condition.wait(lock, [this, &running] { return !queue.empty() || !running.load(); });

    if (queue.empty()) 
        return false;

    event = queue.front();
    queue.pop();
    return true;
}