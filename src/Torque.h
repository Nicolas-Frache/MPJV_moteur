#pragma once
#include "Vector.h"

class CorpsRigide; // Déclaration anticipée de la classe CorpsRigide

class Torque {
public:
    Torque(CorpsRigide* corpsRigide, Vector torque, float duration);

    float updateTimeElapsed(float dt);

    // Propriétés publiques pour simplifier l'accès (peut être modifié en fonction de vos besoins)
    Vector torque; // Torsion appliquée par la force
    float duration; // Durée d'application de la force

    CorpsRigide* corpsRigide; // Référence vers le corps rigide affecté
    float elapsedTime; // Temps écoulé depuis l'application de la force
};

