#pragma once
#include "ofMain.h"

class ProjectileMenu {
public:
    void setup();
    void draw();
    int getSelectedType();
    void setSelectedType(int type);

private:
    int selectedType;
};