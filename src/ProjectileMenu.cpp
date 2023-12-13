#include "ProjectileMenu.h"

ProjectileMenu::ProjectileMenu() {
    // Constructeur par défaut
}

void ProjectileMenu::setup() {
    selectedType = 0; // Initialisation avec le premier type de projectile sélectionné
    showMenu = true; // Afficher le menu par défaut
}

void ProjectileMenu::draw() {

    if (!showMenu) {
		return;
	}

    float buttonX = 20;
    float buttonY = 20;
    float buttonWidth = 300;
    float buttonHeight = 40;
    float spacing = 10;

    ProjectileMenu::drawButton(buttonX, buttonY, buttonWidth, buttonHeight, "Appuyer sur 1 pour lancer une balle");
    ProjectileMenu::drawButton(buttonX, 1*(spacing+ buttonHeight) + buttonY, buttonWidth, buttonHeight, "Appuyer sur 2 pour lancer un boulet");
    ProjectileMenu::drawButton(buttonX, 2*(spacing + buttonHeight) + buttonY, buttonWidth, buttonHeight, "Appuyer sur 3 pour lancer un laser");
    ProjectileMenu::drawButton(buttonX, 3*(spacing + buttonHeight) + buttonY, buttonWidth, buttonHeight, "Appuyer sur 4 pour lancer\nun CorpsRigide en rotation");
    ProjectileMenu::drawButton(buttonX, 4*(spacing + buttonHeight) + buttonY, buttonWidth, buttonHeight, "Appuyer sur p pour mettre\nle jeu en pause");
    ProjectileMenu::drawButton(buttonX, 5*(spacing + buttonHeight) + buttonY, buttonWidth, buttonHeight, "Appuyer sur r pour afficher\nle repere");
    ProjectileMenu::drawButton(buttonX, 6*(spacing + buttonHeight) + buttonY, buttonWidth, buttonHeight, "Appuyer sur m pour masquer\nle menu");
}


void ProjectileMenu::setSelectedType(int type) {
    // Assurez-vous que le type sélectionné est valide (par exemple, entre 1 et 3)
    if (type >= 1 && type <= 4) {
        selectedType = type;
    }
}

void ProjectileMenu::drawButton(int x, int y, int w, int h, char* text){
  ofSetColor(255);
  ofDrawRectRounded(x, y, w, h, 5);
  ofSetColor(0);
  ofDrawBitmapString(text, x + 10, y + 20);
}

int ProjectileMenu::getSelectedType() {
    return selectedType;
}

void ProjectileMenu::setShowMenu(bool show) {
    showMenu = show;
}