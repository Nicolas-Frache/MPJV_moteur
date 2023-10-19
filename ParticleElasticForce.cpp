#include "ParticleElasticForce.h"
#include "ParticleElasticForce.h"

ParticleElasticForce::ParticleElasticForce(float elasticConstant) :
    _elasticConstant(elasticConstant) {
    // Constructeur de la classe, initialise la constante d'élasticité
}

void ParticleElasticForce::updateForce(Particle* particle, float duration) {
    // Assurez-vous que le pointeur particle n'est pas nul
    if (!particle) {
        return;
    }

    // Calculez la déformation de l'élastique par rapport à la position de repos
    float displacement = particle->getPosition().norm() - particle->getPosition().norm();

    // Calculez la force élastique en fonction de la déformation et de la constante d'élasticité
    float elasticForceMagnitude = -_elasticConstant * displacement;

    // Calculez la direction opposée à la déformation
    Vector elasticForceDirection = -particle->getPosition().normalize();

    // Calculez la force en utilisant la direction et la magnitude
    Vector elasticForce = elasticForceDirection * elasticForceMagnitude;

    // Ajoutez la force élastique à la particule avec la durée spécifiée
    particle->applyForce(elasticForce, duration);
}
