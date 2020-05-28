#pragma once

#include <string>

/**
 * This class will act as a mapping between a C++ object and the database
 * And therefore will have all the methods that will allow to fetch results, update entries and insert new entries
 */
class TCPDumpEntry
{
    long dumpID = 0L;
    std::string srcIP = "";
    std::string dstIP = "";
    std::string location = "";
    std::string timestamp = "";
    
    public:
    TCPDumpEntry(){};
    /**
     * Constructor for testing purposes
     * @param timestamp: timestamp in tcpdump format (for example 13:18:11.863706)
     */
    TCPDumpEntry(std::string srcIp, std::string dstIP, std::string timestamp, std::string location);
    /**
     * Constructor for after we parse the file
     */
    TCPDumpEntry(std::string srcIp, std::string dstIP, std::string timestamp);
    /**
     * Constructor for db output of db
     */
    TCPDumpEntry(int argc, char **argv, char **azColName);

    const std::string & getTimestamp()
    {
        return timestamp;
    }
    const std::string & getSrcIp()
    {
        return srcIP;
    }
    const std::string & getDstIp()
    {
        return dstIP;
    }

    const std::string & getLocation()
    {
        return location;
    }

    void setLocation(std::string location)
    {
        this->location = location;
    }

    static void createTable();
    static void truncateDB();    
    void insertInDb();
    void updateInDb();
    static void fetchResults(int page);
    static void fetchResultsCount();
};