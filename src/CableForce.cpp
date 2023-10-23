#include "CableForce.h"

CableForce::CableForce(Particle* A, Particle* B, float maxLength, float duration_) : Force(A,duration_)
{
	_maxLength = maxLength;
	_base = B; //en gros ici la force modifie A selon la distance entre A et B. B non modifi� (et B peut �tre genre fixe par ex)
}

CableForce::CableForce(Particle* A, Vector B, float maxLength, float duration_) : Force(A, duration_)
{
	_maxLength = maxLength;
	_base = new Particle(B, 0, 0, 0); //ici on cr�e un point fixe pour accrocher le cable
}


Vector CableForce::value() //getter de la force
{
	return direction;
}

void CableForce::updateForce(Particle* particle, float duration)
{
	if (!particle) {
		return;
	}

	Vector cableVector = _base->getPosition() - particle->getPosition();
	float distance = cableVector.norm();
	Vector opposingForce = Vector(0, 0, 0); //� remplir en dessous

	if (distance > _maxLength) {
		Vector blockingForce = cableVector;
		blockingForce.normalize();

		if (_base->getMass() == 0) {
			//cas base fixe (masse infinie)
			opposingForce = blockingForce * (_maxLength - distance); //voire ptet juste annuler les forces normales?
		}
		else {
			//base non point fixe
			opposingForce = blockingForce * (particle->getMass() / (particle->getMass() + _base->getMass()));
		}
	}
	else {
				//cas o� le cable n'est pas tendu
		opposingForce = Vector(0, 0, 0);
	}
	direction = opposingForce;
}
