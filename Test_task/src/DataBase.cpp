#include "DataBase.h"
#include "utils.h"
#include <iostream>


DataBase::DataBase(const std::string& filename) 
{
    int rc = sqlite3_open(filename.c_str(), &db_);
    if (rc) { std::cerr << "Cannot open DB: " << sqlite3_errmsg(db_) << std::endl; }
    else
    {
        std::cout << "The database was opened successfully: " << filename << std::endl;
        createTable();
    }
}

DataBase::~DataBase() { if (db_) sqlite3_close(db_); }

void DataBase::createTable() 
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS events ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "timestamp TEXT, "
        "event_id INTEGER, "
        "parameter_1 INTEGER, "
        "parameter_2 INTEGER, "
        "parameter_3 INTEGER, "
        "note TEXT "
        ");";
    char* errMsg = nullptr;

    if (sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) 
    {
        std::cerr << "Error creating table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void DataBase::insertEvent(const Event& e, int logLevel) 
{
    if (!db_) return;

    std::string sql_query;

    switch (logLevel) 
    {
    case 0:
        sql_query = "INSERT INTO events (timestamp, event_id) VALUES (?, ?);";
        break;
    case 1:
        sql_query = "INSERT INTO events (timestamp, event_id, parameter_1) VALUES (?, ?, ?);";
        break;
    case 2:
    default:
        sql_query = "INSERT INTO events (timestamp, event_id, parameter_1, parameter_2, parameter_3, note) VALUES (?, ?, ?, ?, ?, ?);";
        break;
    }

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db_, sql_query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Error preparing request: " << sqlite3_errmsg(db_) << std::endl;
        if (stmt) sqlite3_finalize(stmt);
        return;
    }

    std::string formattedTimestamp = (logLevel == 0) ? getFormattedTime(e.timestamp) : getFormattedDateTime(e.timestamp);

    int bindIndex = 1;
    sqlite3_bind_text(stmt, bindIndex++, formattedTimestamp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, bindIndex++, e.event_id);

    if (logLevel >= 1)
        sqlite3_bind_int(stmt, bindIndex++, e.parameter_1);
    if (logLevel >= 2) 
    {
        sqlite3_bind_int(stmt, bindIndex++, e.parameter_2);
        sqlite3_bind_int(stmt, bindIndex++, e.parameter_3);
        sqlite3_bind_text(stmt, bindIndex++, e.note.c_str(), -1, SQLITE_TRANSIENT);
    }

    if (sqlite3_step(stmt) != SQLITE_DONE) 
        std::cerr << "Error inserting event: " << sqlite3_errmsg(db_) << std::endl;

    sqlite3_finalize(stmt);
}