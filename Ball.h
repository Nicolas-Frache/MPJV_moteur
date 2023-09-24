#pragma once
#include "../MPJV_moteur/src/Particle.h"
#include "../MPJV_moteur/src/Vector.h"

class Ball : public Particle
{
private:
    // Attributs privés de la classe Ball
    Vector _position = Vector(0, 0, 0);
    Vector _velocity = Vector(0, 0, 0);
    Vector _force = Vector(0, 0, 0);
    Vector _rotation = Vector(0, 0, 0);

    float _invertedMass = 1.0f; // Masse inversée (1/masse)
    float _rotationZ;
    float _size = 1.0f;

    ofColor _color = ofColor(255, 255, 255); // Couleur par défaut

public:
    // Constructeur de la classe Ball
    Ball(float X, float Y, float Z, float invertedMass, ofColor color);

    // Méthodes permettant de définir les attributs de la balle
    void setPos(float X, float Y, float Z);
    void setPos(Vector);
    void setMass(float invertedMass);
    void setColor(ofColor color);
    void setSize(float size);
    void setForce(Vector force);
    void setRotationZ(float rotationZ);
    void setVelocity(Vector velocity);

    // Méthodes permettant d'obtenir les attributs de la balle
    Vector getPos();
    float getInvMass();
    ofColor getColor();
    float getSize();
    Vector getForce();
    float getRotationZ();
    Vector getVelocity();

    // Méthodes pour mettre à jour la balle et la dessiner
    void update();
    void draw();

    // Méthode pour appliquer une force à la balle
    void applyForce(float forceX, float forceY, float forceZ);

    // Méthode pour intégrer les équations du mouvement (non utilisée dans le code)
    void integrer(float dt);
};
