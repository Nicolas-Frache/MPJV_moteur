#include "ParticleCableForce.h"

ParticleCableForce::ParticleCableForce(float maxLength) :
    _maxLength(maxLength) {
    // Constructeur de la classe, initialise la longueur maximale du c�ble
}

void ParticleCableForce::updateForce(Particle* particle, float duration) {
    // Assurez-vous que le pointeur particle n'est pas nul
    if (!particle) {
        return;
    }

    // Calculez la longueur actuelle du c�ble
    float currentLength = particle->getPosition().norm();

    // Si la longueur d�passe la longueur maximale du c�ble, calculez la force du c�ble
    if (currentLength > _maxLength) {
        float cableForceMagnitude = (currentLength - _maxLength);

        // Calculez la direction oppos�e � la position actuelle
        Vector cableForceDirection = -particle->getPosition().normalize();

        // Calculez la force en utilisant la direction et la magnitude
        Vector cableForce = cableForceDirection * cableForceMagnitude;

        // Ajoutez la force du c�ble � la particule avec la dur�e sp�cifi�e
        particle->applyForce(cableForce, duration);
    }
}
