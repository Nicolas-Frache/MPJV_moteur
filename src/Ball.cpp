#include "Ball.h"
#include "Particle.h"

// Constructeur de la classe Ball qui initialise la balle avec une position, une masse invers�e et une couleur
Ball::Ball(float X, float Y, float Z, float invertedMass, ofColor color, float size)
    : Particle(X, Y, Z, invertedMass, color, size) {

    _rotationZ = 0;
    rotation = Vector(0, 0, 0);
    restitution = 0.5;
    friction = 0.5;
}

Ball::Ball(Vector position, float invertedMass, ofColor color, float size)
   : Particle(position.x(), position.y(), position.z(), invertedMass, color, size){

}

// M�thode de mise � jour de la balle
void Ball::update() {
    Particle::update();
    //cout << "BALL " << this->getVelocity() << endl;
    _rotationZ += velocity.z() * 0.1; // Mise � jour de la rotation Z
}
