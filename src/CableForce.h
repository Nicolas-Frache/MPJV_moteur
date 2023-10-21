#pragma once
#include "Force.h"
class CableForce :
    public Force
{
public:
    float _maxLenght;
    Particle* _base; //parce qu'on a besoin de la position et de la v�locit� du point, m�me si il est fixe
    CableForce(Particle* A, Particle* B, float maxLength, float duration_);
    CableForce(Particle* A, Vector B, float maxLength, float duration_);
    Vector CableForce::value() override;
    void CableForce::updateForce(Particle* particle, float duration) override;
};

