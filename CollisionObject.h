#pragma once
#include "Particle.h"

class CollisionObject {
public:
    // M�thodes pour la d�tection de collision
    virtual bool checkCollision(const Particle& particle) const = 0;
    virtual void resolveCollision(Particle& particle) const = 0;
};


