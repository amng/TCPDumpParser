#include "../../include/utils/Constants.hpp"
#include "../../include/menu/MenusManager.hpp"
#include "../../include/menu/TCPDumpTypeMenu.hpp"

TCPDumpTypeMenu::TCPDumpTypeMenu()
{
    prompt = "Choose TCPDump stop condition";
    
    addMenuEntry(TCPDP_MENU_OPTION::TIME, []{getMenuContextInstance()->setTCPDumpStopConditionType(TCPDumpStopType::TCPDUMPSTOP_TIME); showMenu(MenuType::TypeLimitMenu);});
    addMenuEntry(TCPDP_MENU_OPTION::PACKETS, []{getMenuContextInstance()->setTCPDumpStopConditionType(TCPDumpStopType::TCPDUMPSTOP_PACKET); showMenu(MenuType::TypeLimitMenu);});
    addMenuEntry(TCPDP_MENU_OPTION::BACK, []{showMenu(MenuType::TypeMainMenu);});
    addMenuEntry(TCPDP_MENU_OPTION::EXIT, []{ exit(0); });
}