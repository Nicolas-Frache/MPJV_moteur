#include "Particle.h"
#include <limits>

Particle::Particle(float X, float Y, float Z, float invertedMass, ofColor color, float size):
	Particle::Particle(Vector(X, Y, Z), invertedMass, color, size) {
}

Particle::Particle(Vector position, float invertedMass, ofColor color, float size) {
	this->position = position;
	this->invertedMass = invertedMass;
	this->color = color;
	this->size = size;

	this->sphere = ofSpherePrimitive(10, 10);
	this->sphere.setRadius(size);

	// Gravite
	applyForce(0, -9.8, 0, numeric_limits<float>::max());
}

// Gestion de la position

void Particle::setPos(float X, float Y, float Z) {
	position.set(X, Y, Z);
}

// M�thode pour d�finir la position de la particule en utilisant un objet Vector
void Particle::setPos(Vector position) {
	position = position;
}


// Gestion de la masse

void Particle::setMass(float mass) {
	if (mass == 0) {
		Particle::setInfinitMass();
		return;
	}
	invertedMass = 1 / mass;
}

void Particle::setInvMass(float invertedMass) {
	invertedMass = invertedMass;
}

void Particle::setInfinitMass() {
	invertedMass = 0;
}

float Particle::getMass() {
	if (invertedMass == 0) {
		return 0;
	}
	return 1 / invertedMass;
}

float Particle::getInvMass() {
	return invertedMass;
}

// Gestion de l'apparence

void Particle::draw() {
	ofEnableDepthTest();
	ofSetColor(color);
	sphere.setPosition(position.x(), position.y(), position.z());
	sphere.draw();
}


void Particle::update() {
	float dt = ofGetLastFrameTime();
	integrer(dt);
	if (duration != -1.0f) {
		//on affiche la durée restante
		duration -= dt;
		if (duration < 0.0f) {
			//cas doit etre gere par les classes contenant des listes de particules,
			//car si on "delete this", on ne peut plus it�rer sur la liste
			//car une particule de la liste n'existera pas (null error je suppose)
		}
	}
}

void Particle::applyForce(Vector force, float duration) {
	_forces.push_back(Force(force, duration));
}

void Particle::applyForce(float forceX, float forceY, float forceZ, float duration) {
	_forces.push_back(Force(Vector(forceX, forceY, forceZ), duration));
}

void Particle::bounce(Vector normal) {
	velocity = velocity - (normal * ((1+restitution) * velocity.scalar_product(normal)));
	Vector tangent = velocity - (normal * velocity.scalar_product(normal));
	velocity = tangent * friction + normal * velocity.scalar_product(normal);
}

void Particle::integrer(float dt) {
	// On itere sur les forces actives
	auto it = _forces.begin();
	while (it != _forces.end()) {
		Force& force = *it;
		float applicationTime = force.updateTimeElapsed(dt);

		velocity += force.direction * invertedMass * applicationTime;
		//notes : melange acceleration force

		if (applicationTime != dt) {
			it = _forces.erase(it); // Suppression de la force si sa duree est terminee
		}
		else {
			++it; // Element suivant
		}
	}

	// On met a jour la position
	position += (velocity * dt);
}
