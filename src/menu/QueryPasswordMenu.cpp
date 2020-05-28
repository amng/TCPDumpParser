#include <stdlib.h> 
#include "../../include/menu/MenusManager.hpp"
#include "../../include/menu/QueryPasswordMenu.hpp"

QueryPasswordMenu::QueryPasswordMenu()
{
    prompt = TCPDP_MENU_PROMPT::PASSWORD;
}

void QueryPasswordMenu::goTo(std::string &s)
{
    int res = 1;
    //check if password is root passsword otherwise ask for user input again
    if (!s.empty())
    {
        std::string testSudoCommand = "echo " + s + " | sudo -S ls > /dev/null 2>&1";
        res = system(testSudoCommand.c_str());
    }
    
    if (res != 0)
    {
        errorMsg = TCPDP_MENU_ERROR::PASSWORD;
        showMenu(MenuType::TypePasswordMenu);
        return;
    }
    getMenuContextInstance()->setPassword(s);
    showMenu(MenuType::TypeStartDummy);
}