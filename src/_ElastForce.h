#pragma once
#include "Force.h"
class ElastForce :
    public Force
{
public:
    Particle* _base;
    float maxLength;
    float springConstant;

    ElastForce(Particle* particle_, Particle* base_, float maxLength_, float springConstant_, float duration_);
    Vector ElastForce::value() override;
    void ElastForce::updateForce(Particle* particle, float duration) override;
    float ElastForce::updateTimeElapsed(float time) override;

};

