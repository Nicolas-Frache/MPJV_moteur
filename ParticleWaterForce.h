#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleForceRegistry.h"

class ParticleWaterForce : public ParticleForceGenerator {
public:
    ParticleWaterForce(float waterDensity, float waterDragCoefficient);
    virtual void updateForce(Particle* particle, float duration);
private:
    float _waterDensity;
    float _waterDragCoefficient;
};