#include "Laser.h"
#include "Particle.h"

Laser::Laser(Vector startPoint, Vector direction, float invertedMass, ofColor color, float size)
	: Particle(startPoint, invertedMass, color, size) {

	this->direction = direction;
	// Retrait de la gravit�
	if (!this->_forces.empty()) {
		this->_forces.pop_front();
	} //TODO: genre faire �a bien sinon pop empty->crash
}
