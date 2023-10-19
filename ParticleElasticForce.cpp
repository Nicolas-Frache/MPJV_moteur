#include "ParticleElasticForce.h"
#include "ParticleElasticForce.h"

ParticleElasticForce::ParticleElasticForce(float elasticConstant) :
    _elasticConstant(elasticConstant) {
    // Constructeur de la classe, initialise la constante d'�lasticit�
}

void ParticleElasticForce::updateForce(Particle* particle, float duration) {
    // Assurez-vous que le pointeur particle n'est pas nul
    if (!particle) {
        return;
    }

    // Calculez la d�formation de l'�lastique par rapport � la position de repos
    float displacement = particle->getPosition().norm() - particle->getPosition().norm();

    // Calculez la force �lastique en fonction de la d�formation et de la constante d'�lasticit�
    float elasticForceMagnitude = -_elasticConstant * displacement;

    // Calculez la direction oppos�e � la d�formation
    Vector elasticForceDirection = -particle->getPosition().normalize();

    // Calculez la force en utilisant la direction et la magnitude
    Vector elasticForce = elasticForceDirection * elasticForceMagnitude;

    // Ajoutez la force �lastique � la particule avec la dur�e sp�cifi�e
    particle->applyForce(elasticForce, duration);
}
