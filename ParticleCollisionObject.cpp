#include "ParticleCollisionObject.h"
#include "Vector.h"

ParticleCollisionObject::ParticleCollisionObject(const Vector& center, float radius)
    : center(center), radius(radius) {}

bool ParticleCollisionObject::checkCollision(const Particle& particle) const {
    // V�rifiez si la particule est � l'int�rieur de la sph�re englobante
    Vector offset = particle.getPosition() - center;
    return offset.norm() < radius;
}

void ParticleCollisionObject::resolveCollision(Particle& particle) const {
    // Force pour corriger la position de la particule
    Vector offset = particle.getPosition() - center;
    float overlap = radius - offset.norm();
    Vector correction = offset.normalize() * overlap;
    particle.setPos(particle.getPosition() + correction);
}
