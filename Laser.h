#pragma once

#include "Particle.h"
#include "Vector.h"

class Laser : public Particle {
public:
    Laser(float _x1, float _y1, float _z1, float _x2, float _y2, float _z2, float mass_);

    void update() override;
    void draw() override;

private:
    Vector _direction;
    float _length;
};
