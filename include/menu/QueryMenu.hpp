#pragma once
#include <string>
#include <iostream> 
#include <climits>
#include "../utils/DisplayUtils.hpp"

class QueryMenu
{
    protected:
        std::string name = "";
        std::string prompt = "";
        std::string errorMsg = "";
    public:
        QueryMenu(){};
        virtual ~QueryMenu() {};
        std::string getName() {return name;}
        
        virtual void goTo(std::string & s) = 0;

        virtual void display()
        {
            clearScreen();
            std::string option;
            showAppTitle();   
            std::cout << std::endl << std::endl;
            if (!errorMsg.empty())
                std::cout << "ERROR:" << errorMsg << std::endl << std::endl;
            else
                std::cout << std::endl << std::endl;
            errorMsg = "";
            std::cout << prompt << " ";
            std::getline (std::cin, option);
            if(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                display();
            }
            else
            {
                goTo(option);
            }
        }
};