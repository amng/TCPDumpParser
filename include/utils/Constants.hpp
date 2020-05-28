#pragma once
#include <string>

//TCpDP (TCP Dump parser)
namespace TCPDP_PATH
{
    static const std::string DATA_PATH = "Data";
    static const std::string DB_PATH = DATA_PATH+"/TCPDumpSql.db";
    static const std::string DUMP_PATH = DATA_PATH+"/tcpdump.dump";
}

namespace TCPDP_NETWORK
{
    static const std::string IP_LOCATION_BASE_URL = "https://ip2c.org/?ip=";
    static const std::string PRIVATE_IP_LABEL = "Private"; 
}

namespace TCPDP_DB
{
    static const int PAGE_SIZE = 10;
}

namespace TCPDP_TIME
{
    static const std::string DATE_FORMAT = "%d %B %Y, %H:%M";
}

namespace TCPDP_APP
{
    static const std::string APP_NAME = "TCPDumpParser";
    static const std::string APP_VERSION = "1.0";
}

namespace TCPDP_MENU_OPTION
{
    static const std::string START = "Start";
    static const std::string BACK_MAIN_MENU = "Back to MainMenu";
    static const std::string UPDATE_RESULTS = "Update Results";
    static const std::string NEXT_PAGE = "Next Page";
    static const std::string PREV_PAGE = "Previous Page";
    static const std::string TIME = "Time";
    static const std::string PACKETS = "Packets";
    static const std::string BACK = "Back";
    static const std::string EXIT = "Exit";
}

namespace TCPDP_MENU_PROMPT
{
    static const std::string GENERIC_OPTION = "Please choose an option";
    static const std::string STOP_PACKET = "Number of packets until stop: ";
    static const std::string STOP_TIME = "Number of seconds until stop: ";
    static const std::string PASSWORD = "Root password (in order to run TCPDump): ";
}

namespace TCPDP_MENU_ERROR
{
    static const std::string LIMIT = "Invalid Value! Please input numeric value...";
    static const std::string PASSWORD =  "Invalid Password!";
}

namespace TCPDP_REGEX
{
    static const std::string IP = "(\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3})\\.\\d+";
    static const std::string TIMESTAMP = "(\\d{2}:\\d{2}:\\d{2}.\\d{6})";
    static const std::string PRIVATE_IP = "^(192\\.168|10\\.|172\\.(1[6-9]|2[0-9]|3[0-1]))";
}

enum TCPDumpStopType
{
    TCPDUMPSTOP_PACKET,
    TCPDUMPSTOP_TIME
};