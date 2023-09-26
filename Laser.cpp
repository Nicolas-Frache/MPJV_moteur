#include "Laser.h"
#include "ofMain.h"

Laser::Laser(float x1, float y1, float z1, float x2, float y2, float z2, float mass)
    : Particle(Vector(x1, y1, z1), mass), _direction(Vector(x2 - x1, y2 - y1, z2 - z1).normalize()), _length(Vector(x2 - x1, y2 - y1, z2 - z1).norm()) {}


void Laser::update() {
    float dt = ofGetLastFrameTime();

    // Mettez à jour la position du laser en fonction de sa direction et de sa vitesse initiale
    Vector newPosition = getPos() + (_direction * getVelocity().norm() * dt);

    // Assurez-vous que le laser n'a pas dépassé sa longueur maximale
    Vector endPosition = getPos() + (_direction * _length);
    if ((newPosition - getPos()).norm2() <= _length * _length) {
        setPos(newPosition);
    }
    else {
        // Si le laser a dépassé sa longueur maximale, définissez sa position à sa position maximale
        setPos(endPosition);
    }
}


void Laser::draw() {
    ofSetColor(0, 0, 0);  // Couleur du laser (rouge)
    ofSetLineWidth(10);     // Épaisseur de la ligne du laser

    // Dessinez le laser en utilisant la position et la direction
    Vector endPosition = getPos() + (_direction * _length);
    ofDrawLine(getPos().x(), getPos().y(), getPos().z(), endPosition.x(), endPosition.y(), endPosition.z());
}
