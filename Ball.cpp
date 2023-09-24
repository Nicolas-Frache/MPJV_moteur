#include "Ball.h"
#include "../MPJV_moteur/src/Particle.h"

// Constructeur de la classe Ball qui initialise la balle avec une position, une masse invers�e et une couleur
Ball::Ball(float X, float Y, float Z, float invertedMass, ofColor color)
    : Particle(X, Y, Z, invertedMass, color) {

}

// M�thode pour d�finir la position de la balle
void Ball::setPos(float X, float Y, float Z) {
    _position.set(X, Y, Z);
}

// M�thode pour d�finir la position de la balle en utilisant un objet Vector
void Ball::setPos(Vector position) {
    _position = position;
}

// M�thode pour d�finir la masse invers�e de la balle
void Ball::setMass(float invertedMass) {
    _invertedMass = invertedMass;
}

// M�thode pour d�finir la couleur de la balle
void Ball::setColor(ofColor color) {
    _color = color;
}

// M�thode pour d�finir la taille de la balle
void Ball::setSize(float size) {
    _size = size;
}

// M�thode pour d�finir la v�locit� de la balle
void Ball::setVelocity(Vector velocity) {
    _velocity = velocity;
}

// M�thode pour d�finir la force appliqu�e � la balle
void Ball::setForce(Vector force) {
    _force = force;
}

// M�thode pour d�finir la rotation Z de la balle
void Ball::setRotationZ(float rotationZ) {
    _rotationZ = rotationZ;
}

// M�thode pour obtenir la position de la balle
Vector Ball::getPos() {
    return _position;
}

// M�thode pour obtenir la masse invers�e de la balle
float Ball::getInvMass() {
    return _invertedMass;
}

// M�thode pour obtenir la couleur de la balle
ofColor Ball::getColor() {
    return _color;
}

// M�thode pour obtenir la taille de la balle
float Ball::getSize() {
    return _size;
}

// M�thode pour obtenir la v�locit� de la balle
Vector Ball::getVelocity() {
    return _velocity;
}

// M�thode pour obtenir la force appliqu�e � la balle
Vector Ball::getForce() {
    return _force;
}

// M�thode pour obtenir la rotation Z de la balle
float Ball::getRotationZ() {
    return _rotationZ;
}

// M�thode de mise � jour de la balle
void Ball::update() {
    _velocity += _force * _invertedMass; // Mise � jour de la v�locit� en fonction de la force (� adapter pour dt)
    //_force = Vector(0, 0, 0); // R�initialisation de la force (peut �tre utilis�e pour l'int�gration avec dt)
    cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;
    _position += _velocity;
    _rotationZ += _force.z() * 0.1; // Mise � jour de la rotation Z
    cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;

    cout << "Adresse de monObjet Balle : " << this << std::endl;
}

// M�thode pour dessiner la balle
void Ball::draw() {
    ofSetColor(getColor());
    ofPushMatrix();
    ofTranslate(_position.x(), _position.y(), _position.z());
    ofRotateZ(_rotationZ * RAD_TO_DEG);

    // Dessiner la balle
    ofDrawCircle(0, 0, 0, _size);

    // Dessiner un petit cercle color� au centre de la balle
    ofSetColor(ofColor::green); // Couleur du point
    ofDrawCircle(15, 0, 0, 2); // Position relative du point par rapport � la balle (0,0,0)

    ofPopMatrix();
}

// M�thode pour appliquer une force � la balle
void Ball::applyForce(float forceX, float forceY, float forceZ) {
    _force += Vector(forceX, forceY, forceZ);
}

// M�thode pour int�grer les �quations du mouvement (non utilis�e dans ce code)
void Ball::integrer(float dt) {
    _velocity += _force * _invertedMass * dt;
    _position += _velocity * dt;
    _force = Vector(0, 0, 0);
}
