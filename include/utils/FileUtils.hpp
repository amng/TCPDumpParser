#pragma once
#include "Constants.hpp"
#include <experimental/filesystem>

bool createDataDir()
{
    return std::experimental::filesystem::create_directories(TCPDP_PATH::DATA_PATH);
}


