// ForceRotationnelle.cpp
#include "ForceRotationnelle.h"
#include "CorpsRigide.h"

ForceRotationnelle::ForceRotationnelle(CorpsRigide* corpsRigide, Vector torque, float duration)
    : corpsRigide(corpsRigide), torque(torque), duration(duration), elapsedTime(0.0f) {}

float ForceRotationnelle::updateTimeElapsed(float dt) {
    elapsedTime += dt;
    return elapsedTime;
}

void ForceRotationnelle::applyTorque() {
    corpsRigide->applyRotation(torque * elapsedTime);
}