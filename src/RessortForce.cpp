#include "RessortForce.h"

RessortForce::RessortForce(Particle* particle_, Particle* base_, float maxLength_, float springConstant_, float duration_) :
	Force(particle_, duration_),
	_base(base_),
	restLength(maxLength_),
	springConstant(springConstant_)
{
}

void RessortForce::updateForce(Particle* particle, float duration)
{
    if (!particle) {
        return;
    }

    Vector springVector = _base->getPosition() - particle->getPosition();
    float displacement = springVector.norm() - restLength;

    Vector springDirection = springVector.normalize();

    // Calcul de la force de ressort en utilisant la loi de Hooke
    Vector springForce = springDirection * (springConstant * displacement);
    direction = springForce;
}
