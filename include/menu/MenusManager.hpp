#pragma once

#include "MainMenu.hpp"
#include "TCPDumpTypeMenu.hpp"
#include "QueryPasswordMenu.hpp"
#include "QueryTCPDumpLimit.hpp"
#include "MenuContext.hpp"
#include "ResultsMenu.hpp"
class TaskManager;

//TODO rename this file to something more considerate and move it somewhere else
enum MenuType
{
    TypeMainMenu,
    TypeTCPDumpTypeMenu,
    TypePasswordMenu,
    TypeLimitMenu,
    TypeResultMenu,
    TypeStartDummy
};

extern MenuContext * getMenuContextInstance();
extern MainMenu * getMainMenuInstance();
extern TCPDumpTypeMenu * getTCPDumpTypeMenuInstance();
extern QueryPasswordMenu * getQueryPasswordMenuInstance();
extern QueryTCPDumpLimit * getLimitMenuInstance();
extern ResultsMenu * getResultMenuInstance();
extern TaskManager * getTaskManagerInstance();
extern void showMenu(MenuType type);