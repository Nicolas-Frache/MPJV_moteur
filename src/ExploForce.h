#pragma once
#include "Force.h"


class ExploForce :
    public Force
{
public:
    Vector _explosionCenter;
    float _explosionRadius;
    float _explosionForce;

    ExploForce(Particle* A, Vector explosionCenter, float explosionRadius, float explosionForce);
    Vector ExploForce::value() override;
    void ExploForce::updateForce(Particle* particle, float duration) override;    
};

