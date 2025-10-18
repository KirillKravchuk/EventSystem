#pragma once

#include <mutex>
#include <memory>
#include <string>
#include "Logger.h"
#include "utils.h"


struct Event;

class LoggerLevel2 : public Logger
{
public:
    explicit LoggerLevel2(const std::string& fileName);
    void Write(const Event& e) override;
};