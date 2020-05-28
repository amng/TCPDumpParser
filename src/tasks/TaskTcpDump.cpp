#include <sstream>
#include "../../include/tasks/TaskTcpDump.hpp"

std::string TaskTcpDump::getCommonOptions()
{
    std::ostringstream os;
    os << " -nn -i any > " <<TCPDP_PATH::DUMP_PATH << " 2>&1";
    return os.str();
}


void TaskTcpDump::runForNPackets(int packetCount)
{
    std::ostringstream os;
    os << "echo " << getMenuContextInstance()->getPassword() << " | sudo -S tcpdump -c " << packetCount << getCommonOptions();
    system(os.str().c_str());
}

void TaskTcpDump::runForNTime(int time)
{
    std::ostringstream os;
    os << "echo " << getMenuContextInstance()->getPassword() << " | sudo -S timeout " << time << " tcpdump " << getCommonOptions();
    system(os.str().c_str());  
}

void TaskTcpDump::runnable()
{
    const int stopConditionValue = getMenuContextInstance()->getTCPDumpStopConditionValue();
    if (getMenuContextInstance()->getTCPDumpStopConditionType() == TCPDumpStopType::TCPDUMPSTOP_PACKET)
    {
        //std::cout << "PACKET THREAD  " << std::endl;
        runForNPackets(stopConditionValue);
    }
    else 
    {
        //std::cout << "TIME THREAD " << stopConditionValue << std::endl;
        runForNTime(stopConditionValue);
    }
    getMenuContextInstance()->finishedTCPDump.store(true);
    //std::cout << "Finished Running" << std::endl; 
}