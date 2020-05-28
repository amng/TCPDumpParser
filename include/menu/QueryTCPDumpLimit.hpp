#pragma once

#include "QueryMenu.hpp"

class QueryTCPDumpLimit : public QueryMenu
{
    public:
    QueryTCPDumpLimit();
    ~QueryTCPDumpLimit(){};
    virtual void goTo(std::string & s);
};