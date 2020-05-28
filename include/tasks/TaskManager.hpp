#pragma once
#include <string>
#include "TaskTcpDump.hpp"
#include "TaskDB.hpp"
#include "TaskUpdateLocation.hpp"


/*
The class responsible for controlling all the other tasks (threads).
This class will make sure that all the threads can be stopped and destroyed correctly and will also start them when needed
*/
class TaskManager
{
    private:
    TaskTcpDump * tdump = nullptr;
    TaskDB * tdb = nullptr;
    TaskUpdateLocation *tupl = nullptr;

    public:
    TaskManager() {}

    void stopAll()
    {
        if (tdump && tdump->isRunning())
        {
            tdump->forceStop();
        }
        if (tdump)
        {
            delete tdump;
            tdump = nullptr;
        }
        if (tdb && tdb->isRunning())
        {
            tdb->forceStop();
        }
        if (tdb)
        {
            delete tdb;
            tdb = nullptr;
        }
        if (tupl && tupl->isRunning())
        {
            tupl->forceStop();
        }
        if (tupl)
        {
            delete tupl;
            tupl = nullptr;
        }
    }

    void fetchData()
    {
        stopAll();
        tdump = new TaskTcpDump();
        tdump->run();
        tdb = new TaskDB();
        tdb->run();
        tupl = new TaskUpdateLocation();
        tupl->run();
    }

};