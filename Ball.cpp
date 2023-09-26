#include "Ball.h"
#include "Vector.h"
#include "Particle.h"

Ball::Ball(float x_, float y_, float z_, float mass_)
    : Ball(Vector(x_, y_, z_), mass_) { }

Ball::Ball(Vector position_, float mass_)
    : Particle(position_, mass_, ofColor_<unsigned char>::pink, 15) { 
    setRestitution(0.8);  // Réglage de la restitution et du frottement selon vos besoins
    setFriction(0.2);
}

void Ball::update() {
    float dt = ofGetLastFrameTime();
    Particle::integrer(3 * dt);
}

void Ball::draw() {
    // Dessin de la balle
    Particle::draw();
}
