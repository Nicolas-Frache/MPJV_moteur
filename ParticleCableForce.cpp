#include "ParticleCableForce.h"

ParticleCableForce::ParticleCableForce(float maxLength) :
    _maxLength(maxLength) {
    // Constructeur de la classe, initialise la longueur maximale du câble
}

void ParticleCableForce::updateForce(Particle* particle, float duration) {
    // Assurez-vous que le pointeur particle n'est pas nul
    if (!particle) {
        return;
    }

    // Calculez la longueur actuelle du câble
    float currentLength = particle->getPosition().norm();

    // Si la longueur dépasse la longueur maximale du câble, calculez la force du câble
    if (currentLength > _maxLength) {
        float cableForceMagnitude = (currentLength - _maxLength);

        // Calculez la direction opposée à la position actuelle
        Vector cableForceDirection = -particle->getPosition().normalize();

        // Calculez la force en utilisant la direction et la magnitude
        Vector cableForce = cableForceDirection * cableForceMagnitude;

        // Ajoutez la force du câble à la particule avec la durée spécifiée
        particle->applyForce(cableForce, duration);
    }
}
