#include "ContactObject.h"
#include "Particle.h"


ContactObject::ContactObject(const Vector& contactPoint, float collisionDistance)
    : contactPoint(contactPoint), collisionDistance(collisionDistance) {}

bool ContactObject::checkCollision(const Particle& particle) const {
    Vector offset = particle.getPosition() - contactPoint;
    return offset.norm() < collisionDistance;
}

void ContactObject::resolveCollision(Particle& particle) const {
    Vector offset = particle.getPosition() - contactPoint;
    if (offset.norm() < collisionDistance) {
        float overlap = collisionDistance - offset.norm();
        Vector correction = offset.normalize() * overlap;
        particle.setPos(particle.getPosition() + correction);
    }
}