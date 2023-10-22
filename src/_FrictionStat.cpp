#include "FrictionStat.h"

FrictionStat::FrictionStat(Particle* particle_, Vector direction_, float friction_, float normal_, float duration_) : Force(particle_, direction_, duration_) {
	friction = friction_;

	//on parcourt la liste des forces de particle_ afin de rrécupérer uniquement la composante normale
	Vector temp = Vector(0, 0, 0);
	for (auto it = particle_->_forces.begin(); it != particle_->_forces.end(); ++it) {
		//OK faut que je mette tout dans temp, mais me faut la direction de normale bref jvais voir le reste
	}

	
	normal = normal_; //TODO: faut utiliser les forces perpendiculaires à la surface de contact. ça peut être gravité mais pas que selon contexte
} //en input pour normal suffit d'input normal.normalize() pour avoir la bonne valeur (la direction de friction n'en dépend pas)
	//donc probablement gérer en dehors de la classe la récup des forces normales (genre avec la liste des forces de la particule?)

Vector FrictionStat::value() {
	float magnitude = friction * normal;
	Vector friction = direction;
	friction.normalize();
	friction *= magnitude; //verif le sens de la force pour *- ou *+
	return friction;
}
