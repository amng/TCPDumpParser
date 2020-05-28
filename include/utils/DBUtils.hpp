#pragma once
#include <sqlite3.h>
#include <iostream>
#include <functional>
#include "Constants.hpp"
#include <mutex>
#include <condition_variable> 
#include "../menu/MenusManager.hpp"
#include "../model/TCPDumpEntry.hpp"


static int runSqlStatement(const std::string & sql, 
                           int (*callback)(void *, int , char **, char **)=nullptr,
                           std::string tablePath=TCPDP_PATH::DB_PATH)
{
    std::unique_lock<std::mutex> lck(getMenuContextInstance()->dbMTX);
    getMenuContextInstance()->dbCV.wait(lck, []{return getMenuContextInstance()->canAccessDB.load();});
    getMenuContextInstance()->blockDBAccess();
    sqlite3 *db;
    int rc;

    rc = sqlite3_open_v2(tablePath.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_EXCLUSIVE, nullptr);

    char *szErrMsg = 0;

    if (callback)
    {
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &szErrMsg);
    }
    else
    {
        rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &szErrMsg);
    }
    
    if (rc != SQLITE_OK)
    {
        sqlite3_free(szErrMsg);
    }

    sqlite3_close(db);
    getMenuContextInstance()->enableDBAccess();

    lck.unlock();
    getMenuContextInstance()->dbCV.notify_all();

    return rc;
}

static int runSqlReadOnlyStatement(const std::string & sql, 
                           int (*callback)(void *, int , char **, char **)=nullptr,
                           int flags=SQLITE_OPEN_READONLY | SQLITE_OPEN_FULLMUTEX,
                           std::string tablePath=TCPDP_PATH::DB_PATH)
{
    //runSqlStatement(sql, callback);
    sqlite3 *db;
    int rc = sqlite3_open_v2(tablePath.c_str(), &db, flags, nullptr);
    char *szErrMsg = 0;
    if (callback)
    {
        rc = sqlite3_exec(db, sql.c_str(), callback, 0, &szErrMsg);
    }
    else
    {
        rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &szErrMsg);
    }
    
    if(rc != SQLITE_OK)
    {
        std::cout << "SQL Error: " << szErrMsg << std::endl;
        sqlite3_free(szErrMsg);
    }
    sqlite3_close(db);
    return 0;
}



static void clearDB()
{
    TCPDumpEntry::truncateDB();
}


static void createDB(std::string tablePath=TCPDP_PATH::DB_PATH)
{
    char *szErrMsg = 0;
    sqlite3 *db;
    // open database
    int rc = sqlite3_open(tablePath.c_str(), &db);
    if (rc)
    {
        std::cout << "Can't open database\n";
        exit(1);
    }
    sqlite3_close(db);
    return;
}

static void initDB()
{
    TCPDumpEntry::createTable();
}