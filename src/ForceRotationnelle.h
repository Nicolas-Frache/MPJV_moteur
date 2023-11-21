#pragma once
#include "Vector.h"

class CorpsRigide; // D�claration anticip�e de la classe CorpsRigide

class ForceRotationnelle {
public:
    ForceRotationnelle(CorpsRigide* corpsRigide, Vector torque, float duration);

    float updateTimeElapsed(float dt);

    // D'autres m�thodes ou membres si n�cessaire...

    // Propri�t�s publiques pour simplifier l'acc�s (peut �tre modifi� en fonction de vos besoins)
    Vector torque; // Torsion appliqu�e par la force
    float duration; // Dur�e d'application de la force

    CorpsRigide* corpsRigide; // R�f�rence vers le corps rigide affect�
    float elapsedTime; // Temps �coul� depuis l'application de la force
};

