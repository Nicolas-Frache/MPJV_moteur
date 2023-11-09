#pragma once
#include <Particle.h>
#include "particleforcegenerator.cpp"

class ParticleForceRegistry {
public:
	struct ParticleForceRegistration {
		Particle* particle;
		ParticleForceGenerator* fg;
	};

	typedef std::vector<ParticleForceRegistration*> Registry;
	Registry registrations;


public:
	void addRegister(Particle* particle, ParticleForceGenerator* pfg) {
		ParticleForceRegistration* pfr = new ParticleForceRegistration();
		pfr->particle = particle;
		pfr->fg = pfg;
		registrations.push_back(pfr);
	}

	void remove(Particle* particle, ParticleForceGenerator* pfg) {
		Registry::iterator i = registrations.begin();
		for (; i != registrations.end(); i++) {
			if ((*i)->particle == particle && (*i)->fg == pfg) {
				registrations.erase(i);
				break;
			}
		}
	}

	void clear() {
		registrations.clear();
	}

	void updateForces(float duration) {
		Registry::iterator i = registrations.begin();
		for (; i != registrations.end(); i++) {
			(*i)->fg->updateForce((*i)->particle, duration);
		}
	}

};

