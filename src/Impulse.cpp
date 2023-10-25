#include "Impulse.h"

// Créer une impulsion entre deux particules
Impulse::Impulse(Particle *object1, Particle *object2)
{
	// Les particules étant des sphères, on peut considérer que l'impact se fait sur l'axe qui relie les deux centres
	Vector normal = (object1->getPosition() - object2->getPosition()).normalize();

	// On récupère la vitesse de chaque objet
	Vector velocity1 = object1->getVelocity();
	Vector velocity2 = object2->getVelocity();

	// On calcule la vitesse relative
	Vector relativeVelocity = velocity1 - velocity2;

	// On projette la vitesse relative sur l'axe de collision
	float relativeVelocityNorm = relativeVelocity.scalar_product(normal);

	// On calcule le coefficient de restitution
	float restitution = object1->restitution * object2->restitution;

	// On calcule la magnitude de l'impulsion
	float magnitude = (1.0f + restitution) * relativeVelocityNorm / (object1->invertedMass + object2->invertedMass);

	// On répartit l'impulsion sur les deux objets
	float impulse1 = -magnitude / object1->invertedMass;
	float impulse2 = magnitude / object2->invertedMass;

	// On applique l'impulsion
	object1->setVelocity(velocity1 + normal * impulse1);
	object2->setVelocity(velocity2 + normal * impulse2);

}

// Créer une impulsion entre deux corps rigides
Impulse::Impulse(Particle* object1, Particle* object2, Vector impactPoint)
{
	// TODO (pour la phase 3)
}