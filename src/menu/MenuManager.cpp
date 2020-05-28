#include "../../include/utils/DBUtils.hpp"
#include "../../include/tasks/TaskManager.hpp"
#include "../../include/menu/MenusManager.hpp"


MenuContext * getMenuContextInstance()
{
    static MenuContext * context;
    if (!context)
        context = new MenuContext();
    return context;
}

MainMenu * getMainMenuInstance()
{
    static MainMenu * mainMenu;
    if (!mainMenu)
        mainMenu = new MainMenu();
    return mainMenu;
}

TCPDumpTypeMenu * getTCPDumpTypeMenuInstance()
{
    static TCPDumpTypeMenu * tcpdumpTypeMenu;
    if (!tcpdumpTypeMenu)
        tcpdumpTypeMenu = new TCPDumpTypeMenu();
    return tcpdumpTypeMenu;
}

QueryPasswordMenu * getQueryPasswordMenuInstance()
{
    static QueryPasswordMenu * passwordMenu;
    if (!passwordMenu)
        passwordMenu = new QueryPasswordMenu();
    return passwordMenu;
}

QueryTCPDumpLimit * getLimitMenuInstance()
{
    static QueryTCPDumpLimit * limitMenu;
    if (!limitMenu)
        limitMenu = new QueryTCPDumpLimit();
    return limitMenu;
}

ResultsMenu * getResultMenuInstance()
{
    static ResultsMenu * resultsMenu;
    if (!resultsMenu)
        resultsMenu = new ResultsMenu();
    return resultsMenu;
}

TaskManager * getTaskManagerInstance()
{
    static TaskManager * taskManager;
    if (!taskManager)
        taskManager = new TaskManager();
    return taskManager;
}

void showMenu(MenuType type)
{
    switch(type)
    {
        case MenuType::TypeMainMenu:
            getTaskManagerInstance()->stopAll();
            getMenuContextInstance()->resetTaskStates();
            clearDB();
            getMainMenuInstance()->display();
            return;
        case MenuType::TypeTCPDumpTypeMenu:
            getTCPDumpTypeMenuInstance()->display();
            return;
        case MenuType::TypePasswordMenu:
            getQueryPasswordMenuInstance()->display();
            return;
        case MenuType::TypeLimitMenu:
            getLimitMenuInstance()->display();
            return;
        case MenuType::TypeStartDummy:
            getTaskManagerInstance()->fetchData();
        case MenuType::TypeResultMenu:
            getResultMenuInstance()->display();
    }
}