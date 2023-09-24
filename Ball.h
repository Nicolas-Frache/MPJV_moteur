#pragma once
#include "../MPJV_moteur/src/Particle.h"
#include "../MPJV_moteur/src/Vector.h"

class Ball : public Particle
{
private:
    // Attributs priv�s de la classe Ball
    Vector _position = Vector(0, 0, 0);
    Vector _velocity = Vector(0, 0, 0);
    Vector _force = Vector(0, 0, 0);
    Vector _rotation = Vector(0, 0, 0);

    float _invertedMass = 1.0f; // Masse invers�e (1/masse)
    float _rotationZ;
    float _size = 1.0f;

    ofColor _color = ofColor(255, 255, 255); // Couleur par d�faut

public:
    // Constructeur de la classe Ball
    Ball(float X, float Y, float Z, float invertedMass, ofColor color);

    // M�thodes permettant de d�finir les attributs de la balle
    void setPos(float X, float Y, float Z);
    void setPos(Vector);
    void setMass(float invertedMass);
    void setColor(ofColor color);
    void setSize(float size);
    void setForce(Vector force);
    void setRotationZ(float rotationZ);
    void setVelocity(Vector velocity);

    // M�thodes permettant d'obtenir les attributs de la balle
    Vector getPos();
    float getInvMass();
    ofColor getColor();
    float getSize();
    Vector getForce();
    float getRotationZ();
    Vector getVelocity();

    // M�thodes pour mettre � jour la balle et la dessiner
    void update();
    void draw();

    // M�thode pour appliquer une force � la balle
    void applyForce(float forceX, float forceY, float forceZ);

    // M�thode pour int�grer les �quations du mouvement (non utilis�e dans le code)
    void integrer(float dt);
};
