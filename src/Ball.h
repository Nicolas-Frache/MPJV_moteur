#pragma once
#include "Particle.h"
#include "Vector.h"

class Ball : public Particle{
public:
    float _rotationZ;
    Vector rotation;

    // Constructeur de la classe Ball
    Ball(float X, float Y, float Z, float invertedMass, ofColor color, float size);
    Ball(Vector position, float invertedMass, ofColor color, float size);


    // M�thodes pour mettre � jour la balle et la dessiner
    void update() override;
;
};
