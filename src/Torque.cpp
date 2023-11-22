// ForceRotationnelle.cpp
#include "Torque.h"
#include "CorpsRigide.h"

Torque::Torque(CorpsRigide* corpsRigide, Vector torque, float duration)
    : corpsRigide(corpsRigide), torque(torque), duration(duration), elapsedTime(0.0f) {}

float Torque::updateTimeElapsed(float dt) {
    elapsedTime += dt;
    return elapsedTime;
}
