// ForceRotationnelle.cpp
#include "ForceRotationnelle.h"
#include "CorpsRigide.h"

ForceRotationnelle::ForceRotationnelle(CorpsRigide* corpsRigide, Vector torque, float duration)
    : corpsRigide(corpsRigide), torque(torque), duration(duration), elapsedTime(0.0f) {}

float ForceRotationnelle::updateTimeElapsed(float dt) {
    elapsedTime += dt;
    if (duration > 0.0f && elapsedTime >= duration) {
        // La force a dépassé sa durée d'application, vous pouvez la supprimer ou la désactiver
        corpsRigide->removeTorque(this);
    }
    return elapsedTime;
}