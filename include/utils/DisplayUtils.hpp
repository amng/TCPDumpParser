#pragma once

#include <iostream>
#include "Constants.hpp"

static void clearScreen()
{
    for (int i = 0; i < 100; i++)
        std::cout << std::endl;
}

static void showAppTitle()
{
    std::cout << "=======================================" << std::endl;
    std::cout << "========== " << TCPDP_APP::APP_NAME << " " << TCPDP_APP::APP_VERSION << " ==========" << std::endl;
    std::cout << "=======================================" << std::endl << std::endl << std::endl;
}