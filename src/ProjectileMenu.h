#pragma once
#include "ofMain.h"

class ProjectileMenu {
public:
    ProjectileMenu();
    void setup();
    void draw();
    int getSelectedType();
    void setShowMenu(bool show);
    void setSelectedType(int type);

    bool showMenu = true;

private:
    int selectedType;
};