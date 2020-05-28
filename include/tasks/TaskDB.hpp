#pragma once

#include <vector>
#include "TaskInterface.hpp"
#include "../utils/Constants.hpp"

/**
 * This class is responsible for reading the tcpdump data that was stored in a file and store it in a database
 */
class TaskDB: public TaskInterface
{   
    private:
    public:
    TaskDB(){}
    ~TaskDB();
    
    virtual void runnable();
};