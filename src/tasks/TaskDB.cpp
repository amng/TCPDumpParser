#include "../../include/tasks/TaskDB.hpp"
#include "../../include/model/TCPDumpEntry.hpp"
#include "../../include/menu/MenusManager.hpp"
#include <fstream>
#include <iostream>
#include <regex>



void TaskDB::runnable()
{
    std::ifstream myfile (TCPDP_PATH::DUMP_PATH);
    while(!myfile.is_open())
        myfile = std::ifstream(TCPDP_PATH::DUMP_PATH);
    if (myfile.is_open())
    {
        std::string line;
        bool lineRead = false;
        std::ostringstream dumpRegexExpression;
        dumpRegexExpression << TCPDP_REGEX::TIMESTAMP << " IP " << TCPDP_REGEX::IP << " > " << TCPDP_REGEX::IP;

        std::regex rgx(dumpRegexExpression.str(), std::regex_constants::ECMAScript);
        while (!getMenuContextInstance()->finishedTCPDump.load() || std::getline(myfile,line))
        {
            std::smatch match;
            if (std::regex_search(line.cbegin(), line.cend(), match, rgx))
            {
                TCPDumpEntry(std::string(match[2]), std::string(match[3]), std::string(match[1]), "Downloading").insertInDb();
            }
        }
        myfile.close();
    }
    getMenuContextInstance()->finishedTCPParse.store(true);
    //std::cout << "Finished Running db task" << std::endl;
}



TaskDB::~TaskDB()
{
}