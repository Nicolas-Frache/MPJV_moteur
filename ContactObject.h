#pragma once
#include "Vector.h"
#include "Particle.h"

class ContactObject {
private:
    Vector contactPoint;
    float collisionDistance;

public:
    ContactObject(const Vector& contactPoint, float collisionDistance);

    virtual bool checkCollision(const Particle& particle) const = 0;
    virtual void resolveCollision(Particle& particle) const = 0;
};
