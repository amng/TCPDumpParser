#pragma once

#include <vector>
#include <math.h> 
#include <atomic>
#include "memory"
#include <mutex>
#include <queue>
#include "../model/TCPDumpEntry.hpp"
#include "../utils/Constants.hpp"
#include <condition_variable> 

/**
 * Class responsible for managing the state of the application
 * */
class MenuContext
{
    TCPDumpStopType TCPDumpStopConditionType  = TCPDumpStopType::TCPDUMPSTOP_PACKET;
    int TCPDumpStopConditionValue = 1;
    std::string password = "";
    int currentPage = 0;
    long totalNumberResults = 0;
    long totalNumberResultsWithoutLoacation = 0;
    std::vector<std::unique_ptr<TCPDumpEntry>> resultsPage;
    public:
    std::queue<TCPDumpEntry> toUpdate;
    std::atomic<bool> finishedTCPDump;
    std::atomic<bool> finishedTCPParse;
    std::atomic<bool> finishedProcessingLocationItems;
    std::mutex dbMTX;
    std::condition_variable dbCV;
    volatile std::atomic<bool> canAccessDB;

    MenuContext() { 
        resetTaskStates(); 
        std::lock_guard<std::mutex> lk(dbMTX);
        canAccessDB.store(true);
        dbCV.notify_all();
    }
    ~MenuContext() {}


    void blockDBAccess()
    {
        canAccessDB.store(false);
    }

    void enableDBAccess()
    {
        canAccessDB.store(true);
    }

    bool allTasksFinished()
    {
        return finishedTCPDump.load() && finishedTCPParse.load() && finishedProcessingLocationItems.load();
    }
    

    void resetTaskStates()
    {
        finishedTCPDump.store(false);
        finishedTCPParse.store(false);
        finishedProcessingLocationItems.store(false);
    }

    void clearReults()
    {
        resultsPage.clear();
    }

    void addResult(std::unique_ptr<TCPDumpEntry> entry)
    {
        resultsPage.push_back(std::move(entry));
    }

    void setPassword(std::string password)
    {
        this->password = password;
    }

    void setTCPDumpStopConditionValue(int TCPDumpStopConditionValue)
    {
        this->TCPDumpStopConditionValue = TCPDumpStopConditionValue;
    }

    void setTCPDumpStopConditionType(TCPDumpStopType TCPDumpStopConditionType)
    {
        this->TCPDumpStopConditionType = TCPDumpStopConditionType;
    }

    const std::string & getPassword()
    {
        return password;
    }

    const TCPDumpStopType & getTCPDumpStopConditionType()
    {
        return TCPDumpStopConditionType;
    }

    const int getTCPDumpStopConditionValue()
    {
        return TCPDumpStopConditionValue;
    }

    const std::vector<std::unique_ptr<TCPDumpEntry>> & getResults()
    {
        return this->resultsPage;
    }

    const int getResultsCount()
    {
        return this->resultsPage.size();
    }
    
    const int getCurrentPage()
    {
        return currentPage;
    }

    void nextPage()
    {
        currentPage++;
    }

    void previousPage()
    {
        currentPage--;
    }

    void setTotalNumberResults(long totalNumberResults)
    {
        this->totalNumberResults = totalNumberResults;
    }

    void setTotalNumberResultsWithoutLocation(long totalNumberResultsWithoutLoacation)
    {
        this->totalNumberResultsWithoutLoacation = totalNumberResultsWithoutLoacation;
    }

    long getTotalNumberResultsWithoutLocation()
    {
        return this->totalNumberResultsWithoutLoacation;
    }

    int getPageCount()
    {
        return ceil((double)totalNumberResults/(double)TCPDP_DB::PAGE_SIZE);
    }

    bool isNextPageAvailable()
    {
        return getPageCount() > (currentPage+1);
    }

    bool isPrevPageAvailable()
    {
        return currentPage > 0;
    }
};
