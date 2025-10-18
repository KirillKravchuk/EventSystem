#pragma once

#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <atomic>
#include <mutex>
#include "Event.h"

class EventQueue;

class EventGenerator
{
public:
	EventGenerator(EventQueue& queue);
	Event generateEvent();
	std::string generateNote();
	void start();
	void stop();
	void faster();
	void slower();
	void pause();
	void resume();
	bool isRunning() const { return running; }
	
private:
	void run();

	std::atomic<bool> running{ false };
	std::atomic<bool> paused{ false };
	std::thread worker;
	EventQueue& queue;
	std::mt19937 randomGenerator;
	std::uniform_int_distribution<int> event_id;
	std::uniform_int_distribution<int> parameter_1;
	std::uniform_int_distribution<int> parameter_2;
	std::uniform_int_distribution<int> parameter_3;

	std::mutex delayMutex;
	int minDelayMs;
	int maxDelayMs;

	std::vector<std::string> event_templates = 
	{
		"COMMS has entered SCIENCE_DOWNLINK mode as scheduled",
		"OBC has successfully completed scheduled star tracker calibration",
		"Battery temperature T1 is above nominal threshold",
		"Reaction Wheel 3 speed is approaching saturation limit",
		"Primary X-Band Transmitter failure detected. No downlink available",
		"Onboard memory ECC error count critical. Data corruption possible",
		"Payload HSI completed observation sequence successfully",
		"Payload SAR data buffer overflow. Data loss occurred",
		"Onboard Computer watchdog timer reset triggered",
		"Primary gyroscope package reporting anomalous bias drift outside calibration envelope",
		"Sequential Shunt Unit SSU-2 detected a short circuit; faulty string has been isolated",
		"Survival heater HTR-A on propulsion branch enabled; component temperature is rising",
		"Thermistor THRM-14 on payload radiator is reporting open circuit; data is invalid",
		"All platform component temperatures are stable and within nominal flight boundaries",
		"Uplink command decoder fault detected; system has autonomously switched to redundant unit",
		"Sector 4 of the non-volatile memory has been taken offline due to correctable ECC error threshold exceedance"
	};
};

