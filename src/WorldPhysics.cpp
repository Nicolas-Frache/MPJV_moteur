#include "WorldPhysics.h"

WorldPhysics::WorldPhysics()
{
}

WorldPhysics::WorldPhysics(float x_size, float y_size, float z_size)
{
	this->_x_size = x_size;
	this->_y_size = y_size;
	this->_z_size = z_size;
}

void WorldPhysics::update()
{
	updateCollisions();
	updateBoundaries();
	updateRodConstraints();

	// Update particules
	for (Particle* particle : particles) {
		particle->update();
	}
	for (CorpsRigide* corps : corpsRigides) {
		corps->update();
	}
}

void WorldPhysics::addParticle(Particle* particle)
{
	particles.push_back(particle);
}

void WorldPhysics::removeParticle(Particle* particle)
{
	particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
}

void WorldPhysics::addCorps(CorpsRigide* corps)
{
	corpsRigides.push_back(corps);
}

void WorldPhysics::removeCorps(CorpsRigide* corps)
{
	corpsRigides.erase(std::remove(corpsRigides.begin(), corpsRigides.end(), corps), corpsRigides.end());
}

void WorldPhysics::addRodConstraint(Particle* particle1, Particle* particle2, float length)
{
	RodConstraint* rodConstraint = new RodConstraint(particle1, particle2, length);
	rodConstraints.push_back(rodConstraint);
}

void WorldPhysics::removeRodConstraint(Particle* particle1, Particle* particle2)
{
	for (int i = 0; i < rodConstraints.size(); i++) {
		RodConstraint* rodConstraint = rodConstraints[i];
		if (rodConstraint->getParticle1() == particle1 && rodConstraint->getParticle2() == particle2) {
			rodConstraints.erase(rodConstraints.begin() + i);
			return;
		}
	}
}


void WorldPhysics::updateCollisions()
{
	for (int i = 0; i < particles.size(); i++) {
		Particle* particle1 = particles[i];
		for (int j = i + 1; j < particles.size(); j++) {
			Particle* particle2 = particles[j];
			// Vérifier si une collision se produit entre les deux particules
			if (particle1->checkCollisionWith(*particle2)) {
				// Résoudre la collision entre les deux particules
				particle1->resolveInterpenetration(*particle2);
				Impulse(particle1, particle2);
			}
			// Vérifiez s'il y a une collision douce
			if (particle1->checkRestingContactWith(*particle2)) {
				// Traite la collision au repos ici
				particle1->resolveRestingContactWith(*particle2);
			}
		}
	}
}

void WorldPhysics::updateBoundaries()
{

	for (Particle* particle : particles) {

		particle->update();

		auto pos = particle->position;
		//cout << "POS: " << pos << endl;

		float x = pos.x(), y = pos.y(), z = pos.z();


		if (x > _x_size || x < -_x_size) {
			if (x > _x_size) {
				particle->setPos(_x_size, y, z);
				particle->bounce(Vector(-1, 0, 0));
			}
			else {
				particle->setPos(-_x_size, y, z);
				particle->bounce(Vector(1, 0, 0));
			}
		}
		if (y > _y_size || y < 0) {
			if (y > _y_size) {
				particle->setPos(x, _y_size, z);
				particle->bounce(Vector(0, -1, 0));
			}
			else {
				particle->setPos(x, 0, z);
				particle->bounce(Vector(0, 1, 0));
			}
		}
		if (z > _z_size || z < -_z_size) {
			if (z > _z_size) {
				particle->setPos(x, y, _z_size);
				particle->bounce(Vector(0, 0, -1));
			}
			else {
				particle->setPos(x, y, -_z_size);
				particle->bounce(Vector(0, 0, 1));
			}
		}
	}

	for (CorpsRigide* corps : corpsRigides) {

		corps->update();

		auto pos = corps->centreMasse->position;
		//cout << "POS: " << pos << endl;

		float x = pos.x(), y = pos.y(), z = pos.z();


		if (x > _x_size || x < -_x_size) {
			if (x > _x_size) {
				corps->centreMasse->setPos(_x_size, y, z);
				corps->centreMasse->bounce(Vector(-1, 0, 0));
			}
			else {
				corps->centreMasse->setPos(-_x_size, y, z);
				corps->centreMasse->bounce(Vector(1, 0, 0));
			}
		}
		if (y > _y_size || y < 0) {
			if (y > _y_size) {
				corps->centreMasse->setPos(x, _y_size, z);
				corps->centreMasse->bounce(Vector(0, -1, 0));
			}
			else {
				corps->centreMasse->setPos(x, 0, z);
				corps->centreMasse->bounce(Vector(0, 1, 0));
			}
		}
		if (z > _z_size || z < -_z_size) {
			if (z > _z_size) {
				corps->centreMasse->setPos(x, y, _z_size);
				corps->centreMasse->bounce(Vector(0, 0, -1));
			}
			else {
				corps->centreMasse->setPos(x, y, -_z_size);
				corps->centreMasse->bounce(Vector(0, 0, 1));
			}
		}
	}

}


void WorldPhysics::updateRodConstraints()
{
	for (RodConstraint* rodConstraint : rodConstraints) {
		rodConstraint->satisfyConstraint();
	}
}
