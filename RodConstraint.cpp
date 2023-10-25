#include "RodConstraint.h"

RodConstraint::RodConstraint(Particle* p1, Particle* p2, float length)
    : particle1(p1), particle2(p2), restLength(length) {}

void RodConstraint::satisfyConstraint() const {
    // Calcule la distance entre les deux particules
    Vector delta = particle2->getPosition() - particle1->getPosition();
    float currentDist = delta.norm();

    // Calcule la correction nécessaire pour atteindre la longueur de tige souhaitée
    float diff = (currentDist - restLength) / (currentDist * (particle1->getInvMass() + particle2->getInvMass()));

    // Applique la correction aux positions des particules
    if (particle1->getInvMass() > 0) {
        particle1->setPos(particle1->getPosition() + delta * particle1->getInvMass() * diff);
    }
    if (particle2->getInvMass() > 0) {
        particle2->setPos(particle2->getPosition() - delta * particle2->getInvMass() * diff);
    }
}

Particle* RodConstraint::getParticle1() const {
    return particle1;
}

Particle* RodConstraint::getParticle2()const {
    return particle2;
}
