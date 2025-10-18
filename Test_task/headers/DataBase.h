#pragma once

#include <sqlite3.h>
#include <string>
#include <iostream>
#include <sstream>
#include "utils.h"
#include "EventGenerator.h"


class DataBase
{
public:
    DataBase(const std::string& filename);
    ~DataBase();

    void insertEvent(const Event& event, int logLevel);

private:
    sqlite3* db_;

    void createTable();
};