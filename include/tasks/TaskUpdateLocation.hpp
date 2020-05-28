#pragma once

#include "TaskInterface.hpp"
#include "../utils/Constants.hpp"

/**
 * The purposeof this class is to update the update locations in the background
 */
class TaskUpdateLocation: public TaskInterface
{   
    private:
    public:
    TaskUpdateLocation(){}
    
    virtual void runnable();
};