#include <ios>
#include <iomanip>
#include <algorithm>
#include "../../include/menu/MenusManager.hpp"
#include "../../include/menu/ResultsMenu.hpp"


ResultsMenu::ResultsMenu()
{
    rebuildMenu();
}

static const std::string WHITE_SQUARE = "\u25AD";

void ResultsMenu::rebuildMenu() 
{
    this->MultiChoiceMenu::rebuildMenu();
    TCPDumpEntry::fetchResultsCount();
    TCPDumpEntry::fetchResults(getMenuContextInstance()->getCurrentPage()); 
    
    prompt = TCPDP_MENU_PROMPT::GENERIC_OPTION;
    if (getMenuContextInstance()->isNextPageAvailable())
    {
        addMenuEntry(TCPDP_MENU_OPTION::NEXT_PAGE, 
        []{
            getMenuContextInstance()->nextPage();
            showMenu(MenuType::TypeResultMenu);
        });
    }

    if (getMenuContextInstance()->isPrevPageAvailable())
    {
        addMenuEntry(TCPDP_MENU_OPTION::PREV_PAGE, 
        []{
            getMenuContextInstance()->previousPage();
            showMenu(MenuType::TypeResultMenu);
        });
    }

    addMenuEntry(TCPDP_MENU_OPTION::UPDATE_RESULTS, 
    []{
        showMenu(MenuType::TypeResultMenu);
    });

    addMenuEntry(TCPDP_MENU_OPTION::BACK_MAIN_MENU, []{showMenu(MenuType::TypeMainMenu);});
    addMenuEntry(TCPDP_MENU_OPTION::EXIT, []{ exit(0); });
}

void drawCharacterNTimes(int num, std::string character)
{
    for (int i = 0 ; i < num; i++)
    {
        std::cout << character;
    }
}

std::string getCroppedString(const std::string & s, size_t maxSize)
{
    if (s.size() > maxSize)
    {
        return s.substr(0, maxSize-1) + "\u2026" + " ";
    }
    return s;
}

void printEntry(const std::unique_ptr<TCPDumpEntry> & entry )
{
    std::ios_base::fmtflags f( std::wcout.flags() );
    std::cout << std::setw(1) << "\u25AF";
    std::cout << " " << std::left << std::setw(29) << getCroppedString(entry->getTimestamp(), 28).c_str();
    std::cout << std::setw(1) << "|";
    std::cout << " " << std::left << std::setw(29) << getCroppedString(entry->getSrcIp(), 28).c_str();
    std::cout << std::setw(1) << "|";
    std::cout << " " << std::left << std::setw(29) << getCroppedString(entry->getDstIp(), 28).c_str();
    std::cout << std::setw(1) << "|";
    std::cout << " " << std::left << std::setw(49) << getCroppedString(entry->getLocation(), 48).c_str();
    std::cout << std::setw(1) << "\u25AF";
    std::wcout.flags( f );
}

void printHeader()
{
    std::ios_base::fmtflags f( std::wcout.flags() );
    std::cout << std::setw(1) << "\u25AF";
    std::cout << " " << std::left << std::setw(29) << "Timestamp";
    std::cout << std::setw(1) << "|";
    std::cout << " " << std::left << std::setw(29) << "Source IP";
    std::cout << std::setw(1) << "|";
    std::cout << " " << std::left << std::setw(29) << "Destination IP";
    std::cout << std::setw(1) << "|";
    std::cout << " " << std::left << std::setw(49) << "Location";
    std::cout << std::setw(1) << "\u25AF";
    std::wcout.flags( f );
}

void ResultsMenu::preDisplay()
{
    rebuildMenu();
    std::ios_base::fmtflags f( std::wcout.flags() );
    //std::wcout << "===== RESULTS ======" << std::endl;
    drawCharacterNTimes(145, WHITE_SQUARE);
    std::cout << std::endl;
    printHeader();
    std::cout << std::endl;
    drawCharacterNTimes(145, WHITE_SQUARE);
    std::cout << std::endl;

    int i = 0;
    for (auto & entry :  getMenuContextInstance()->getResults())
    {
        printEntry(entry);
        std::cout << std::endl;
        if (i < getMenuContextInstance()->getResultsCount()-1)
        {
            drawCharacterNTimes(145, "-");
            std::cout << std::endl;
        }
        i++;
    }
    drawCharacterNTimes(145, WHITE_SQUARE);
    std::wcout.flags( f );
    std::cout << std::endl << "Page " << (getMenuContextInstance()->getCurrentPage()+1) << " out of " << getMenuContextInstance()->getPageCount(); 
    if (!getMenuContextInstance()->allTasksFinished())
    {
        std::cout << std::endl << "Fetching Data..." << std::endl;
    }
    std::wcout << std:: endl<< std:: endl;
}