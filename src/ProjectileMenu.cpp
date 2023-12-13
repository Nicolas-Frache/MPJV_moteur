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

    // Premier bouton
    ofSetColor(255); // Couleur blanche
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5); // rectangle arrondi
    ofSetColor(0); // Couleur noire
    ofDrawBitmapString("Appuyer sur 1 pour lancer une balle", buttonX + 10, buttonY + 20);


    buttonY += buttonHeight + spacing;
    ofSetColor(255); 
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
    ofSetColor(0);
    ofDrawBitmapString("Appuyer sur 2 pour lancer un boulet", buttonX + 10, buttonY + 20);

    buttonY += buttonHeight + spacing;
    ofSetColor(255);
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
    ofSetColor(0);
    ofDrawBitmapString("Appuyer sur 3 pour lancer un laser", buttonX + 10, buttonY + 20);

    buttonY += buttonHeight + spacing;
    ofSetColor(255);
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
    ofSetColor(0);
    ofDrawBitmapString("Appuyer sur 4 pour lancer", buttonX + 10, buttonY + 20);
    ofDrawBitmapString("un CorpsRigide en rotation", buttonX + 10, buttonY + 30);

    buttonY += buttonHeight + spacing;
    ofSetColor(255);
	ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
	ofSetColor(0);
	ofDrawBitmapString("Appuyer sur ! pour afficher", buttonX + 10, buttonY + 20);
    ofDrawBitmapString("le debugging visuel", buttonX + 10, buttonY + 30);

	buttonY += buttonHeight + spacing;
    ofSetColor(255);
	ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
	ofSetColor(0);
	ofDrawBitmapString("Appuyer sur p pour mettre", buttonX + 10, buttonY + 20);
    ofDrawBitmapString("le jeu en pause", buttonX + 10, buttonY + 30);

	buttonY += buttonHeight + spacing;
	ofSetColor(255);
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
    ofSetColor(0);
    ofDrawBitmapString("Appuyer sur r pour afficher", buttonX + 10, buttonY + 20);
    ofDrawBitmapString("le repere", buttonX + 10, buttonY + 30);

    buttonY += buttonHeight + spacing;
    ofSetColor(255);
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5);
    ofSetColor(0);
    ofDrawBitmapString("Appuyer sur m pour masquer", buttonX + 10, buttonY + 20);
    ofDrawBitmapString("le menu", buttonX + 10, buttonY + 30);
}


void ProjectileMenu::setSelectedType(int type) {
    // Assurez-vous que le type sélectionné est valide (par exemple, entre 1 et 3)
    if (type >= 1 && type <= 4) {
        selectedType = type;
    }
}

int ProjectileMenu::getSelectedType() {
    return selectedType;
}

void ProjectileMenu::setShowMenu(bool show) {
    showMenu = show;
}