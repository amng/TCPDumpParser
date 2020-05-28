#pragma once
#include <thread>
#include <iostream>
#include <chrono>
#include "TaskInterface.hpp"
#include "../menu/MenusManager.hpp"

/*The class responsible for running tcpdump until the user defined stop conditions */
class TaskTcpDump : public TaskInterface
{   
    public:
    TaskTcpDump(){}
    std::string getCommonOptions();
    void runForNPackets(int packetCount);
    void runForNTime(int time);    
    virtual void runnable() override;

};