#pragma once
#include "MultiChoiceMenu.hpp"

class ResultsMenu : public MultiChoiceMenu
{
    public:
    ResultsMenu();
    virtual void preDisplay() override;
    virtual void rebuildMenu() override;
};