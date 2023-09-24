#pragma once
#include "../MPJV_moteur/src/Particle.h"
#include "../MPJV_moteur/src/Vector.h"

class Ball : public Particle{
public:
    float _rotationZ;
    Vector rotation;

    // Constructeur de la classe Ball
    Ball(float X, float Y, float Z, float invertedMass, ofColor color, float size);


    // Méthodes pour mettre à jour la balle et la dessiner
    void update() override;
    void draw() override;
;
};
