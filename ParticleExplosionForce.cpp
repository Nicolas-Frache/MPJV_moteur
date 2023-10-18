#include "ParticleExplosionForce.h"

ParticleExplosionForce::ParticleExplosionForce(Vector explosionCenter, float explosionMagnitude) :
    _explosionCenter(explosionCenter), _explosionMagnitude(explosionMagnitude) {
}

void ParticleExplosionForce::updateForce(Particle* particle, float duration) {
    // Assurez-vous que le pointeur particle n'est pas nul
    if (!particle) {
        return;
    }

    // Calculez la direction de la force par rapport au centre de l'explosion
    Vector direction = particle->position - _explosionCenter;

    // Calculez la distance par rapport au centre de l'explosion
    float distance = direction.norm();

    // Calculez la force en fonction de la distance et de l'intensité de l'explosion
    Vector force = direction.normalize() * (_explosionMagnitude / distance);

    // Ajoutez la force à la particule avec une durée spécifiée
    particle->applyForce(force, duration);
}
