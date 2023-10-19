#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleForceRegistry.h"


class ParticleExplosionForce : public ParticleForceGenerator {
public:
    ParticleExplosionForce(Vector explosionCenter, float explosionMagnitude);
    virtual void updateForce(Particle* particle, float duration);
private:
    Vector _explosionCenter;
    float _explosionMagnitude;
};