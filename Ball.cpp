#include "Ball.h"
#include "../MPJV_moteur/src/Particle.h"

// Constructeur de la classe Ball qui initialise la balle avec une position, une masse inversée et une couleur
Ball::Ball(float X, float Y, float Z, float invertedMass, ofColor color)
    : Particle(X, Y, Z, invertedMass, color) {

}

// Méthode pour définir la position de la balle
void Ball::setPos(float X, float Y, float Z) {
    _position.set(X, Y, Z);
}

// Méthode pour définir la position de la balle en utilisant un objet Vector
void Ball::setPos(Vector position) {
    _position = position;
}

// Méthode pour définir la masse inversée de la balle
void Ball::setMass(float invertedMass) {
    _invertedMass = invertedMass;
}

// Méthode pour définir la couleur de la balle
void Ball::setColor(ofColor color) {
    _color = color;
}

// Méthode pour définir la taille de la balle
void Ball::setSize(float size) {
    _size = size;
}

// Méthode pour définir la vélocité de la balle
void Ball::setVelocity(Vector velocity) {
    _velocity = velocity;
}

// Méthode pour définir la force appliquée à la balle
void Ball::setForce(Vector force) {
    _force = force;
}

// Méthode pour définir la rotation Z de la balle
void Ball::setRotationZ(float rotationZ) {
    _rotationZ = rotationZ;
}

// Méthode pour obtenir la position de la balle
Vector Ball::getPos() {
    return _position;
}

// Méthode pour obtenir la masse inversée de la balle
float Ball::getInvMass() {
    return _invertedMass;
}

// Méthode pour obtenir la couleur de la balle
ofColor Ball::getColor() {
    return _color;
}

// Méthode pour obtenir la taille de la balle
float Ball::getSize() {
    return _size;
}

// Méthode pour obtenir la vélocité de la balle
Vector Ball::getVelocity() {
    return _velocity;
}

// Méthode pour obtenir la force appliquée à la balle
Vector Ball::getForce() {
    return _force;
}

// Méthode pour obtenir la rotation Z de la balle
float Ball::getRotationZ() {
    return _rotationZ;
}

// Méthode de mise à jour de la balle
void Ball::update() {
    _velocity += _force * _invertedMass; // Mise à jour de la vélocité en fonction de la force (à adapter pour dt)
    //_force = Vector(0, 0, 0); // Réinitialisation de la force (peut être utilisée pour l'intégration avec dt)
    cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;
    _position += _velocity;
    _rotationZ += _force.z() * 0.1; // Mise à jour de la rotation Z
    cout << "_position: " << _position << " velocity : " << _velocity << ", force : " << _force << endl;

    cout << "Adresse de monObjet Balle : " << this << std::endl;
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

// Méthode pour appliquer une force à la balle
void Ball::applyForce(float forceX, float forceY, float forceZ) {
    _force += Vector(forceX, forceY, forceZ);
}

// Méthode pour intégrer les équations du mouvement (non utilisée dans ce code)
void Ball::integrer(float dt) {
    _velocity += _force * _invertedMass * dt;
    _position += _velocity * dt;
    _force = Vector(0, 0, 0);
}
