#include "Ball.h"
#include "Particle.h"

// Constructeur de la classe Ball qui initialise la balle avec une position, une masse inversée et une couleur

Ball::Ball(Vector position, float invertedMass, ofColor color, float size): 
    Particle::Particle(position, invertedMass, color, size){
    _rotationZ = 0;
    rotation = Vector(0, 0, 0);
}

// Méthode de mise à jour de la balle
void Ball::update() {
    Particle::update();
    _rotationZ += velocity.z() * 0.1; // Mise à jour de la rotation Z
}
