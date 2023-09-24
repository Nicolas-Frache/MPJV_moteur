#include "ProjectileMenu.h"

void ProjectileMenu::setup() {
    selectedType = 0; // Initialisation avec le premier type de projectile sélectionné
}

void ProjectileMenu::draw() {
    // Définir la position de départ des boutons
    float buttonX = 20; // Position en X du premier bouton
    float buttonY = 20; // Position en Y des boutons
    float buttonWidth = 300; // Largeur des boutons
    float buttonHeight = 40; // Hauteur des boutons
    float spacing = 10; // Espacement entre les boutons

    // Dessiner le premier bouton (type 1)
    ofSetColor(255); // Couleur blanche pour le bouton
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5); // Dessiner un rectangle arrondi
    ofSetColor(0); // Couleur noire pour le texte
    ofDrawBitmapString("Appuyer sur 1 pour lancer une balle", buttonX + 10, buttonY + 20); // Afficher le texte

    // Dessiner le deuxième bouton (type 2)
    buttonY += buttonHeight + spacing; // Augmenter la position en Y pour le deuxième bouton
    ofSetColor(255); // Couleur blanche pour le bouton
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5); // Dessiner un rectangle arrondi
    ofSetColor(0); // Couleur noire pour le texte
    ofDrawBitmapString("Appuyer sur 2 pour lancer un boulet", buttonX + 10, buttonY + 20); // Afficher le texte

    // Dessiner le troisième bouton (type 3)
    buttonY += buttonHeight + spacing; // Augmenter la position en Y pour le troisième bouton
    ofSetColor(255); // Couleur blanche pour le bouton
    ofDrawRectRounded(buttonX, buttonY, buttonWidth, buttonHeight, 5); // Dessiner un rectangle arrondi
    ofSetColor(0); // Couleur noire pour le texte
    ofDrawBitmapString("Appuyer sur 3 pour lancer un laser", buttonX + 10, buttonY + 20); // Afficher le texte
}


void ProjectileMenu::setSelectedType(int type) {
    // Assurez-vous que le type sélectionné est valide (par exemple, entre 1 et 3)
    if (type >= 1 && type <= 3) {
        selectedType = type;
    }
}

int ProjectileMenu::getSelectedType() {
    return selectedType;
}