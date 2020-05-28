#include <stdlib.h> 
#include "../../include/utils/Constants.hpp"
#include "../../include/menu/MenusManager.hpp"
#include "../../include/menu/QueryTCPDumpLimit.hpp"

QueryTCPDumpLimit::QueryTCPDumpLimit()
{
    if (getMenuContextInstance()->getTCPDumpStopConditionType() == TCPDumpStopType::TCPDUMPSTOP_PACKET)
        prompt = TCPDP_MENU_PROMPT::STOP_PACKET;
    else
        prompt = TCPDP_MENU_PROMPT::STOP_TIME;
    
}

void QueryTCPDumpLimit::goTo(std::string &s)
{
    int res = 1;
    //check if password is root passsword otherwise ask for user input again
    if (!s.empty())
    {
        try
        {
            getMenuContextInstance()->setTCPDumpStopConditionValue(std::stoi(s));
            res = 0;
        }
        catch(...)
        {
            res = 1;
        }
    }
    if (res != 0)
    {
        errorMsg = TCPDP_MENU_ERROR::LIMIT;
        showMenu(MenuType::TypeLimitMenu);
        return;
    }
    if (getMenuContextInstance()->getPassword().empty())
    {
        showMenu(MenuType::TypePasswordMenu);
    }
    else
    {
        showMenu(MenuType::TypeStartDummy);
    }
    
}