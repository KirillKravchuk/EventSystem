#pragma once

#include <mutex>
#include <memory>
#include <string>
#include "Logger.h"
#include "utils.h"


struct Event;

class LoggerLevel0 : public Logger
{
public:
    explicit LoggerLevel0(const std::string& fileName);
    void Write(const Event& e) override;
};
