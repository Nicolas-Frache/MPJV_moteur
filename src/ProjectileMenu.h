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
    void drawButton(int x, int y, int w, int h, char* text);

    bool showMenu = true;

private:
    int selectedType;
};