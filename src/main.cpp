#include "../include/utils/FileUtils.hpp"
#include "../include/menu/MenusManager.hpp"
#include "../include/utils/DBUtils.hpp"

int main()
{	    
    sqlite3_shutdown();
    sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    sqlite3_initialize();
    createDataDir();
    createDB();
    initDB();
    showMenu(MenuType::TypeMainMenu);
    return 0;
}