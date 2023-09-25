#include "Ball.h"
#include "Particle.h"

// Constructeur de la classe Ball qui initialise la balle avec une position, une masse inversée et une couleur
Ball::Ball(float X, float Y, float Z, float invertedMass, ofColor color, float size)
    : Particle(X, Y, Z, invertedMass, color, size) {

    _rotationZ = 0;
    rotation = Vector(0, 0, 0);
}

// Méthode de mise à jour de la balle
void Ball::update() {
    Particle::update();
    _rotationZ += _velocity.z() * 0.1; // Mise à jour de la rotation Z
}

// Méthode pour dessiner la balle
void Ball::draw() {
    ofSetColor(getColor());
    ofPushMatrix();
    ofTranslate(_position.x(), _position.y(), _position.z());
    ofRotateZ(_rotationZ * RAD_TO_DEG);

    // Dessiner la balle
    ofDrawCircle(0, 0, 0, _size);

    // Dessiner un petit cercle coloré au centre de la balle
    ofSetColor(ofColor::green); // Couleur du point
    ofDrawCircle(15, 0, 0, 2); // Position relative du point par rapport à la balle (0,0,0)

    ofPopMatrix();
}
