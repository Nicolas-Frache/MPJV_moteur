#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleForceRegistry.h"

class ParticleSpringForce : public ParticleForceGenerator {
public:
    ParticleSpringForce(float springConstant, float restLength);
    virtual void updateForce(Particle* particle, float duration);
private:
    float _springConstant;
    float _restLength;
};