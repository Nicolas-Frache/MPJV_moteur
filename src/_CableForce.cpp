#include "CableForce.h"

CableForce::CableForce(Particle* A, Particle* B, float maxLength, float duration_) : Force(A,duration_)
{
	_maxLenght = maxLength;
	_base = B; //en gros ici la force modifie A selon la distance entre A et B. B non modifié (et B peut être genre fixe par ex)
}

CableForce::CableForce(Particle* A, Vector B, float maxLength, float duration_) : Force(A, duration_)
{
	_maxLenght = maxLength;
	_base = new Particle(B, 0, 0, 0); //ici on crée un point fixe pour accrocher le cable
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
	Vector opposingForce = Vector(0, 0, 0); //à remplir en dessous

	if (distance > _maxLenght) {
		Vector blockingForce = cableVector;
		blockingForce.normalize();

		if (_base->getMass() == 0) {
			//cas base fixe (masse infinie)
			opposingForce = blockingForce * (_maxLenght - distance); //voire ptet juste annuler les forces normales?
		}
		else {
			//base non point fixe
			if (particle->getVelocity().norm() * particle->getMass() > _base->getVelocity().norm() * _base->getMass()){
				//cas où A est plus rapide que B
				opposingForce = blockingForce * (_maxLenght - distance);
			}
			else {
				opposingForce = -blockingForce * (_maxLenght - distance);
			}
		}
	}
	direction = opposingForce;
}
