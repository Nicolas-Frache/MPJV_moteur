#pragma once
#include "Particle.h"

class RodConstraint {
public:
    RodConstraint(Particle* p1, Particle* p2, float length);
    void satisfyConstraint() const;
    Particle* getParticle1()const;
    Particle* getParticle2() const;
private:
    Particle* particle1;
    Particle* particle2;
    float restLength;
};
