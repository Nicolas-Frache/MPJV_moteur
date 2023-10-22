#pragma once
#include <list>
#include <Particle.h>
#include <ParticleForceRegistry.cpp>
#include <Gravity.cpp>
class PhysicsEngine{

public:
	// Pointeur vers une liste de pointeurs
	list<Particle*>* particles;
	ParticleForceRegistry forceRegistry;

	PhysicsEngine(list<Particle*>* particles) {
		this->particles = particles;
		this->forceRegistry = ParticleForceRegistry();
		
		for (Particle* p : *particles) {
			this->forceRegistry.add(p, &Gravity());
		}
	}

	void update() {
		float dt = ofGetLastFrameTime();

		computeForce(dt);
		computeVelocityAndUpdatePosition(dt);
	}

	void computeForce(float dt) {
		forceRegistry.updateForces(dt);
	}

	void computeVelocityAndUpdatePosition(float dt) {
		for (Particle* p : *particles) {
			// v' = v + dt * a
			//			avec  a = F / m
			p->velocity += (p->forceAccum * dt) * p->getInvMass();
			// p' = p + dt * v'
			p->position += p->velocity * dt;

			p->clearAccumulator();
		}
	}
};

