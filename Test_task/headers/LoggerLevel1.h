#pragma once

#include <mutex>
#include <memory>
#include <string>
#include "Logger.h"
#include "utils.h"


struct Event;

class LoggerLevel1 : public Logger
{
public:
    explicit LoggerLevel1(const std::string& fileName);
    void Write(const Event& e) override;
};