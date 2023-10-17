#include "FrictionStat.h"

FrictionStat::FrictionStat(Vector direction_, float friction_, float normal_, float duration_) : Force(direction_, duration_) {
	friction = friction_;
	normal = normal_; //TODO: faut utiliser les forces perpendiculaires à la surface de contact. ça peut être gravité mais pas que selon contexte
}

Vector FrictionStat::value() {
	float magnitude = friction * normal;
	Vector friction = direction;
	friction.normalize();
	friction *= magnitude; //verif le sens de la force?
	return friction;
}
