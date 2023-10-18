#pragma once
#include "Particle.h"
#include "Vector.h"
#include "../ParticleForceGenerator.h"
#include "../ParticleForceRegistry.h"

class ParticleElasticForce : public ParticleForceGenerator {
public:
    ParticleElasticForce(float elasticConstant);
    virtual void updateForce(Particle* particle, float duration);
private:
    float _elasticConstant;
};
