#pragma once
#include "Particle.h"

class CollisionObject {
public:
    // Méthodes pour la détection de collision
    virtual bool checkCollision(const Particle& particle) const = 0;
    virtual void resolveCollision(Particle& particle) const = 0;
};


