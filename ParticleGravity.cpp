#include "ParticleGravity.h"
#include "Vector.h"
#include "Particle.h"


ParticleGravity::ParticleGravity(Vector gravityVec) : _gravity(gravityVec) {
}

void ParticleGravity::updateForce(Particle* particle, float duree) {
    if (!particle) {
        return;
    }

    
    if (duree != 0.0f) {
        // Calcul de la force de gravit� : gravit� * masse
        Vector force = _gravity * particle->getMass();

        // Ajoutez la force � la particule
        particle->applyForce(force, duree);
    }
}