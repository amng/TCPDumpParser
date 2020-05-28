#include "../../include/utils/Constants.hpp"
#include "../../include/menu/MenusManager.hpp"
#include "../../include/menu/MainMenu.hpp"

MainMenu::MainMenu()
{
    name = TCPDP_APP::APP_NAME + " " + TCPDP_APP::APP_VERSION;
    prompt = TCPDP_MENU_PROMPT::GENERIC_OPTION;
    addMenuEntry(TCPDP_MENU_OPTION::START, []{showMenu(MenuType::TypeTCPDumpTypeMenu);});
    addMenuEntry(TCPDP_MENU_OPTION::EXIT, []{ exit(0); });
}