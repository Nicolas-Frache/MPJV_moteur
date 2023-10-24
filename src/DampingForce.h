#pragma once
#include "Force.h"
class DampingForce :
    public Force
{
public:
    float _dampingFactor; //facteur d'amort

    DampingForce(Particle* A, float dampingFactor);

    Vector DampingForce::value() override;

    float DampingForce::updateTimeElapsed(float time) override;
};

