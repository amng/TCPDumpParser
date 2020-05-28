#pragma once

#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "Constants.hpp"


/*
    @param 
*/
static std::string convertTimestamp(std::string time)
{
    struct tm dump_tm;
    strptime(time.c_str(), "%H:%M:%S", &dump_tm); //TODO: add some type of validation
    time_t now = std::time(0);
    struct tm * final_tm = localtime(&now);
    final_tm->tm_hour = dump_tm.tm_hour;
    final_tm->tm_min = dump_tm.tm_min;
    std::ostringstream os;
    os << std::put_time(final_tm, TCPDP_TIME::DATE_FORMAT.c_str());
    return os.str();
}
