#pragma once

#include "QueryMenu.hpp"

class QueryPasswordMenu : public QueryMenu
{
    public:
    QueryPasswordMenu();
    ~QueryPasswordMenu(){};
    virtual void goTo(std::string & s);
};