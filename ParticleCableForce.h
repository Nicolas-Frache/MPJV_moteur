#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleForceRegistry.h"

class ParticleCableForce : public ParticleForceGenerator {
public:
    ParticleCableForce(float maxLength);
    virtual void updateForce(Particle* particle, float duration);
private:
    float _maxLength;
};
{
};

