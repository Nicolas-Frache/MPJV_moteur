#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg) {
    ParticleForceRegistration registration;
    registration.particle = particle;
    registration.fg = fg;
    registre.push_back(registration);
}

void ParticleForceRegistry::remove(Particle* particle) {
    for (auto it = registre.begin(); it != registre.end(); ++it) {
        if (it->particle == particle) {
            registre.erase(it);
            return;
        }
    }
}


void ParticleForceRegistry::clear() {
    registre.clear();
}

void ParticleForceRegistry::updateForces(float duration) {
    for (auto& registration : registre) {
        Particle* particle = registration.particle;
        ParticleForceGenerator* fg = registration.fg;
        if (particle && fg) {
            fg->updateForce(particle, duration);
        }
    }
}
