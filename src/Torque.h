#pragma once
#include "Vector.h"

class CorpsRigide; // D�claration anticip�e de la classe CorpsRigide

class Torque {
public:
    Torque(CorpsRigide* corpsRigide, Vector torque, double duration);

    double updateTimeElapsed(double dt);

    // Propri�t�s publiques pour simplifier l'acc�s (peut �tre modifi� en fonction de vos besoins)
    Vector torque; // Torsion appliqu�e par la force
    double remainingTime; // Dur�e d'application de la force

    CorpsRigide* corpsRigide; // R�f�rence vers le corps rigide affect�
    double elapsedTime; // Temps �coul� depuis l'application de la force
};

