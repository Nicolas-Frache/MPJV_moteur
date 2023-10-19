#include "ParticleWaterForce.h"

ParticleWaterForce::ParticleWaterForce(float waterDensity, float waterDragCoefficient) :
    _waterDensity(waterDensity), _waterDragCoefficient(waterDragCoefficient) {
    // Constructeur de la classe, initialise la densité de l'eau et le coefficient de traînée de l'eau
}

void ParticleWaterForce::updateForce(Particle* particle, float duration) {
    if (!particle) {
        return;
    }

    // Calculez la force de traînée de l'eau en fonction de la vitesse de la particule
    Vector velocity = particle->velocity;
    float speed = velocity.norm();
    float dragMagnitude = 0.5 * _waterDensity * speed * speed * _waterDragCoefficient;

    // Calculez la direction opposée à la vitesse de la particule
    Vector dragDirection = -velocity.normalize();

    // Calculez la force de traînée de l'eau en utilisant la formule F = -0.5 * rho * v^2 * Cd
    Vector waterDragForce = dragDirection * dragMagnitude;

    // Ajoutez la force de traînée de l'eau à la particule avec une durée spécifiée
    particle->applyForce(waterDragForce, duration);
}
