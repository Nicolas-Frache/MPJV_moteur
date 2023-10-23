#pragma once
#include "Force.h"
class RessortForce :
    public Force
{
public:
    Particle* _base;
    float restLength;
    float springConstant;

    RessortForce(Particle* particle_, Particle* base_, float maxLength_, float springConstant_, float duration_);
    void RessortForce::updateForce(Particle* particle, float duration) override;
};

