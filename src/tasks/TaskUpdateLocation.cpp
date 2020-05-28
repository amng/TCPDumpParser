#include <sstream>
#include <chrono>
#include "../../include/utils/DBUtils.hpp"
#include "../../include/menu/MenusManager.hpp"
#include "../../include/utils/LocationUtils.hpp"
#include "../../include/tasks/TaskUpdateLocation.hpp"


int updateLocationCallback(void *data, int argc, char **argv, char **azColName){
    TCPDumpEntry temp (argc, argv, azColName);
    temp.setLocation(locationFromIP(temp.getDstIp()));
    getMenuContextInstance()->toUpdate.push(temp);
    return 0;
}

void fetchResultsWithoutLocation()
{
    std::ostringstream os;
    os << "select * from TCPDUMP WHERE location = 'Downloading' limit 10;";
    runSqlStatement(os.str(), &updateLocationCallback);
}

int UpdateResultsWithoutLocationCount(void *data, int argc, char **argv, char **azColName)
{
    getMenuContextInstance()->setTotalNumberResultsWithoutLocation(std::stol(argv[0]));
    return 0;
}

void fetchResultsCount()
{
    std::ostringstream os;
    os << "select COUNT(*) from TCPDUMP WHERE location = 'Downloading';";
    runSqlStatement(os.str(), &UpdateResultsWithoutLocationCount);
}


void updateLocations()
{
    while (!getMenuContextInstance()->finishedTCPParse.load() || getMenuContextInstance()->getTotalNumberResultsWithoutLocation() > 0)
    {
        if (getMenuContextInstance()->canAccessDB.load())
        {
            fetchResultsWithoutLocation();
            fetchResultsCount();
        }
        while ( getMenuContextInstance()->toUpdate.size() > 0 )
        {
            getMenuContextInstance()->toUpdate.front().updateInDb();
            getMenuContextInstance()->toUpdate.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void TaskUpdateLocation::runnable()
{
    updateLocations();
    fetchResultsCount();
    updateLocations(); //make sure we didn't skip the update
    getMenuContextInstance()->finishedProcessingLocationItems.store(true);
    //std::cout << "Finished updating locations" << std::endl;
}
