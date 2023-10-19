#include "ParticleSpringForce.h"

ParticleSpringForce::ParticleSpringForce(float springConstant, float restLength) :
    _springConstant(springConstant), _restLength(restLength) {
    // Constructeur de la classe, initialise la constante de raideur du ressort et la longueur de repos
}

void ParticleSpringForce::updateForce(Particle* particle, float duration) {
    // Assurez-vous que le pointeur particle n'est pas nul
    if (!particle) {
        return;
    }

    // Calculez la direction et la magnitude de la force de ressort
    Vector direction = particle->position - particle->position; // Accédez directement aux membres de Particle
    float currentLength = direction.norm();
    float displacement = currentLength - _restLength;
    float springForceMagnitude = -_springConstant * displacement;

    // Calculez la force en utilisant la direction et la magnitude
    Vector springForce = direction.normalize() * springForceMagnitude;

    // Ajoutez la force de ressort à la particule avec la durée spécifiée
    particle->applyForce(springForce, duration);
}
