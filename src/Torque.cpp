// ForceRotationnelle.cpp
#include "Torque.h"
#include "CorpsRigide.h"

Torque::Torque(CorpsRigide* corpsRigide, Vector torque, double duration)
    : corpsRigide(corpsRigide), torque(torque), remainingTime(duration), elapsedTime(0.0f) {}

double Torque::updateTimeElapsed(double dt) {
    elapsedTime += dt;
    return elapsedTime;
}
