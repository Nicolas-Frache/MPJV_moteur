#include "Particle.h"
#include <limits>
#include "ConstantForce.h"


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
	//TODO: applyForce(new ConstantForce(this, Vector(0, -9.8, 0))); //temporaire
}

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
	Force* f = new Force(this, force, duration);
	_forces.push_back(f);
}

void Particle::applyForce(float forceX, float forceY, float forceZ, float duration) {
	Force* f = new Force(this, Vector(forceX, forceY, forceZ), duration);
	_forces.push_back(f);
}

void Particle::applyForce(Force* force) {
	_forces.push_back(force);
}

void Particle::bounce(Vector normal) {
	velocity = velocity - (normal * ((1+restitution) * velocity.scalar_product(normal)));
	Vector tangent = velocity - (normal * velocity.scalar_product(normal));
	velocity = tangent * friction + normal * velocity.scalar_product(normal);
}

void Particle::integrer(float dt) {
	// On itere sur les forces actives
	//on affiche la taille du tableau de forces
	//cout << "size of forces: " << _forces.size() << endl;
	auto it = _forces.begin();
	while (it != _forces.end()) {
		//Force* force = *it;
		float applicationTime = (*it)->updateTimeElapsed(dt);

		velocity += (*it)->value() * invertedMass * applicationTime;
		//avec force.value on peut utiliser la force pour récup l'accel (Sum(F) = m*a, d'où a = F/m d'où v = F/m * dt)

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



bool Particle::checkCollisionWith(const Particle& other) const {
	float minDistance = this->size + other.size;
	Vector offset = other.position - this->position;
	return offset.norm() < minDistance;
}

bool Particle::checkRestingContactWith(const Particle& other) const {
	float minDistance = this->size + other.size;
	Vector offset = other.position - this->position;
	float distance = offset.norm();

	// Si la distance est inférieure à la somme des rayons, il y a une collision douce
	return distance < minDistance;
}


bool Particle::resolveInterpenetration(Particle& other) {
	float minDistance = this->size + other.size;
	Vector offset = other.position - this->position;
	float distance = offset.norm();

	if (distance < minDistance) {
		Vector correction = offset.normalize() * (minDistance - distance) * 0.5;
		this->position -= correction;
		other.position += correction;
		return true;
	}
	return false;
}

void Particle::resolveRestingContactWith(Particle& other) {
	// Calculez le vecteur de collision et la distance de pénétration
	Vector collisionVector = other.position - this->position;
	float overlap = collisionVector.norm() - (this->size + other.size);

	// Si overlap est positif, il y a une pénétration
	if (overlap > 0) {
		// Répartir la collision
		Vector correction = collisionVector.normalize() * (overlap * 0.5);

		// Appliquez la correction aux deux particules
		this->position -= correction;
		other.position += correction;
	}
}
