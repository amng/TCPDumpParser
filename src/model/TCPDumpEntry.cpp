#include <memory>
#include "../../include/utils/DBUtils.hpp"
#include "../../include/utils/Constants.hpp"
#include "../../include/utils/TimeUtils.hpp"
#include "../../include/utils/LocationUtils.hpp"
#include "../../include/menu/MenusManager.hpp"
#include "../../include/model/TCPDumpEntry.hpp"

TCPDumpEntry::TCPDumpEntry(std::string srcIp, std::string dstIP, std::string timestamp, std::string location)
: srcIP(srcIp), dstIP(dstIP), timestamp(convertTimestamp(timestamp)), location(location)
{}

TCPDumpEntry::TCPDumpEntry(std::string srcIp, std::string dstIP, std::string timestamp)
: srcIP(srcIp), dstIP(dstIP), timestamp(convertTimestamp(timestamp))
{
    location = locationFromIP(dstIP);
}

TCPDumpEntry::TCPDumpEntry(int argc, char **argv, char **azColName)
{
    for(int i = 0; i<argc; i++) {
        std::string column(azColName[i]);
        if (column == "dumpId")
            dumpID = std::stol(argv[i]);
        else if (column == "timestamp")
            timestamp = std::string(argv[i]);    
        else if (column == "srcIp")
            srcIP = std::string(argv[i]);
        else if (column == "dstIp")
            dstIP = std::string(argv[i]);
        else if (column == "location")
            location = std::string(argv[i]);
    }
    //std::cout << std::endl << dumpID << " " << srcIP << " " << dstIP << " " << location << std::endl;
}

void TCPDumpEntry::createTable()
{
    std::string createTableSql = "CREATE TABLE TCPDUMP("
                                 "dumpId INTEGER PRIMARY KEY AUTOINCREMENT,"
                                 "timestamp TEXT,"
                                 "srcIp TEXT,"
                                 "dstIp TEXT,"
                                 "location TEXT);";
    runSqlStatement(createTableSql);
}

void TCPDumpEntry::insertInDb()
{
    std::ostringstream os;
    os << "INSERT INTO TCPDUMP (timestamp, srcIp, dstIp, location) values ('" <<
        timestamp << "', '" << srcIP << "', '" << dstIP << "', '" << location << "');";
    runSqlStatement(os.str());
}

void TCPDumpEntry::updateInDb()
{
    std::ostringstream os;
    os << "UPDATE TCPDUMP set srcIp='" << srcIP << "', dstIp='" << dstIP << "', location='" << location <<
        "', timestamp='" << timestamp << "' WHERE dumpId=" << dumpID << ";";
    //std::cout << os.str() << std::endl;
    runSqlStatement(os.str());
}

void TCPDumpEntry::truncateDB()
{
    std::string truncateSql = "DELETE FROM TCPDUMP;";
    runSqlStatement(truncateSql);
    truncateSql = "DELETE from sqlite_sequence where name='TCPDUMP';";
    runSqlStatement(truncateSql);
}

int fetchResultsCallback(void *data, int argc, char **argv, char **azColName){
   getMenuContextInstance()->addResult(std::make_unique<TCPDumpEntry>(argc, argv, azColName));   
   return 0;
}

int fetchResultsCountCallback(void *data, int argc, char **argv, char **azColName)
{
    getMenuContextInstance()->setTotalNumberResults(std::stol(argv[0]));
    return 0;
}

//Don't block UI :D
void TCPDumpEntry::fetchResults(int page)
{
    getMenuContextInstance()->clearReults();
    int offset = page * TCPDP_DB::PAGE_SIZE;
    std::ostringstream os;
    os << "select * from TCPDUMP limit " << TCPDP_DB::PAGE_SIZE << " offset " << offset;
    runSqlReadOnlyStatement(os.str(), &fetchResultsCallback);
}

void TCPDumpEntry::fetchResultsCount()
{
    getMenuContextInstance()->clearReults();
    std::ostringstream os;
    os << "select COUNT(*) from TCPDUMP";
    runSqlReadOnlyStatement(os.str(), &fetchResultsCountCallback);
}

