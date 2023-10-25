#pragma once
#include "CollisionObject.h"
#include "Particle.h"
#include "Vector.h"

class ParticleCollisionObject : public CollisionObject {
private:
    Vector center;
    float radius;

public:
    ParticleCollisionObject(const Vector& center, float radius);

    bool checkCollision(const Particle& particle) const override;

    void resolveCollision(Particle& particle) const override;
};
