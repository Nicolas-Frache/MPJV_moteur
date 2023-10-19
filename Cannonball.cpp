#include "Cannonball.h"

Cannonball::Cannonball(float X, float Y, float Z, float invertedMass, ofColor color)
    : Ball(X, Y, Z, invertedMass, color) {

}

void Cannonball::setPos(float X, float Y, float Z) {
    _position.set(X, Y, Z);
}

void Cannonball::setPos(Vector position) {
    _position = position;
}

void Cannonball::setMass(float invertedMass) {
    _invertedMass = invertedMass;
}

void Cannonball::setColor(ofColor color) {
    _color = color;
}

void Cannonball::setSize(float size) {
    _size = size;
}

void Cannonball::setVelocity(Vector velocity) {
    _velocity = velocity;
}

void Cannonball::setForce(Vector force) {
    _force = force;
}

void Cannonball::setRotationZ(float rotationZ) {
    _rotationZ = rotationZ;
}

Vector Cannonball::getPos() {
    return _position;
}

float Cannonball::getInvMass() {
    return _invertedMass;
}

ofColor Cannonball::getColor() {
    return _color;
}

float Cannonball::getSize() {
    return _size;
}

Vector Cannonball::getVelocity() {
    return _velocity;
}

Vector Cannonball::getForce() {
    return _force;
}

float Cannonball::getRotationZ() {
    return _rotationZ;
}

void Cannonball::update() {
    _velocity += _force * _invertedMass;
    _rotationZ += _force.z() * 0.1;
    _position += _velocity;
}

void Cannonball::draw() {
    ofSetColor(getColor());
    ofPushMatrix();
    ofTranslate(_position.x(), _position.y(), _position.z());
    ofRotateZ(_rotationZ * RAD_TO_DEG);

    // Dessiner le Cannonball
    ofDrawCircle(0, 0, 0, _size);

    // Dessiner un petit cercle coloré au centre du Cannonball
    ofSetColor(ofColor::red); // Couleur du point (peut être ajustée)
    ofDrawCircle(10, 0, 0, 2); // Position relative au Cannonball (0,0,0), ajustez la taille selon vos besoins

    ofPopMatrix();
}


void Cannonball::applyForce(float forceX, float forceY, float forceZ) {
    _force += Vector(forceX, forceY, forceZ);
}

void Cannonball::integrer(float dt) {
    _velocity += _force * _invertedMass * dt;
    _position += _velocity * dt;
    _force = Vector(0, 0, 0);
}
