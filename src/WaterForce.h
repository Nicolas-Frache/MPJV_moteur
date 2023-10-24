#pragma once
#include "Force.h"
class WaterForce :
    public Force
{
public:
    float _waterDensity;
    float _waterDragCoef;

    WaterForce(Particle* A, float waterDensity, float waterDragCoef, float duration);
    Vector WaterForce::value() override;
    void WaterForce::updateForce(Particle* particle, float duration) override;)
};

