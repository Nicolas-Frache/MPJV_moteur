#include "FrictionStat.h"

FrictionStat::FrictionStat(Vector direction_, float friction_, float normal_, float duration_) : Force(direction_, duration_) {
	friction = friction_;
	normal = normal_; //TODO: faut utiliser les forces perpendiculaires � la surface de contact. �a peut �tre gravit� mais pas que selon contexte
} //en input pour normal suffit d'input normal.normalize() pour avoir la bonne valeur (la direction de friction n'en d�pend pas)
	//donc probablement g�rer en dehors de la classe la r�cup des forces normales (genre avec la liste des forces de la particule?)

Vector FrictionStat::value() {
	float magnitude = friction * normal;
	Vector friction = direction;
	friction.normalize();
	friction *= magnitude; //verif le sens de la force pour *- ou *+
	return friction;
}
