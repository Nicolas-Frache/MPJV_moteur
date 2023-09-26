#pragma once
#include "Particle.h"
#include "Vector.h"
#include <list>

class Ball : public Particle {

public:
    Ball(float x_, float y_, float z_, float mass_);
    Ball(Vector position_, float mass_);

    void update() override;
    void draw() override;

};
