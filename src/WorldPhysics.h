#pragma once

#include "Particle.h"
#include "CorpsRigide.h"
#include <list>

#include "Impulse.h"
#include "RodConstraint.h"

class WorldPhysics
{
	public:
		WorldPhysics();
		WorldPhysics(float x_size, float y_size, float z_size);

		void update();

		float getXSize() { return _x_size; }
		float getYSize() { return _y_size; }
		float getZSize() { return _z_size; }

		void setXSize(float x_size) { this->_x_size = x_size; }
		void setYSize(float y_size) { this->_y_size = y_size; }
		void setZSize(float z_size) { this->_z_size = z_size; }

		void addParticle(Particle* particle);
		void removeParticle(Particle* particle);

		void addCorps(CorpsRigide* corps);
		void removeCorps(CorpsRigide* corps);

		void addRodConstraint(Particle* particle1, Particle* particle2, float length);
		void removeRodConstraint(Particle* particle1, Particle* particle2);

	private:
		vector<Particle*> particles = vector<Particle*>();
		vector<CorpsRigide*> corpsRigides = vector<CorpsRigide*>();
		vector<RodConstraint*> rodConstraints = vector<RodConstraint*>();

		float _x_size = 1000;
		float _y_size = 50000;
		float _z_size = 1000;

		void updateCollisions();

		void updateBoundaries();

		void updateRodConstraints();

		
};

