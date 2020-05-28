#pragma once
#include <string>
#include <iostream> 
#include <vector>
#include <functional>
#include <limits>
#include "../utils/DisplayUtils.hpp"

class MultiChoiceMenu
{
    private:
        std::vector<std::string> options;   
        std::vector<std::function<void()>> functions;
        void clearMenuOptions()
        {
            options.clear();
            functions.clear();
        }
    protected:
        std::string name = "";
        std::string prompt = "";
        void addMenuEntry(std::string option, std::function<void()> function)
        {
            options.push_back(option);
            functions.push_back(function);
        }
        
        virtual void rebuildMenu()
        {
            clearMenuOptions();
        }

        
    public:
        std::string getName() {return name;}
        
        virtual void preDisplay() {};

        virtual void display()
        {
            clearScreen();
            unsigned int option;
            showAppTitle();   
            preDisplay();
            std::cout << std::endl << std::endl;
            size_t optionsSize = options.size();
            for (int i = 0; i < optionsSize; i++)
            {
                std::cout << (i+1) << ". " << options[i] << std::endl;
            }
            std::cout << std::endl << std::endl << prompt << " (1-" << options.size() << "): ";
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            }            
            std::cin >> option;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            if (option - 1 < options.size())
            {
                functions[option-1]();
            }
            else 
            {
                option = 0;
                display();
            }
        }
};