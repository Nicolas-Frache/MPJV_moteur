#include "Particle.h"
#include <limits>

Particle::Particle(float X, float Y, float Z, float invertedMass, ofColor color, float size):
	Particle::Particle(Vector(X, Y, Z), invertedMass, color, size) {
}

Particle::Particle(Vector position, float invertedMass, ofColor color, float size) {
	_position = position;
	_invertedMass = invertedMass;
	_color = color;
	_size = size;
	sphere = ofSpherePrimitive(10, 10);
	sphere.setRadius(_size);

	// Gravit� 
	applyForce(0, -9.8, 0, numeric_limits<float>::max());
}

// Gestion de la position

void Particle::setPos(float X, float Y, float Z) {
	_position.set(X, Y, Z);
}

// M�thode pour d�finir la position de la particule en utilisant un objet Vector
void Particle::setPos(Vector position) {
	_position = position;
}

Vector Particle::getPos() {
	return _position;
}

void Particle::setRestitution(float restitution) {
	this->restitution = restitution;
}

void Particle::setFriction(float friction) {
	this->friction = friction;
}

void Particle::setDuration(float duration) {
	this->duration = duration;
}

float Particle::getDuration() {
	return duration;
}

// Gestion de la masse

void Particle::setMass(float mass) {
	if (mass == 0) {
		Particle::setInfinitMass();
		return;
	}
	_invertedMass = 1 / mass;
}

void Particle::setInvMass(float invertedMass) {
	_invertedMass = invertedMass;
}

void Particle::setInfinitMass() {
	_invertedMass = 0;
}

float Particle::getMass() {
	if (_invertedMass == 0) {
		return 0;
	}
	return 1 / _invertedMass;
}

float Particle::getInvMass() {
	return _invertedMass;
}

// Gestion de l'apparence

void Particle::setColor(ofColor color) {
	_color = color;
}

void Particle::setSize(float size) {
	_size = size;
}

ofColor Particle::getColor() {
	return _color;
}

// M�thode pour obtenir la taille de la particule
float Particle::getSize() {
	return _size;
}

void Particle::draw() {
	ofEnableDepthTest();
	ofSetColor(_color);
	sphere.setPosition(_position.x(), _position.y(), _position.z());
	sphere.draw();
}


void Particle::setVelocity(Vector velocity) {
	_velocity = velocity;
}

void Particle::setVelocity(float X, float Y, float Z) {
	_velocity.set(X, Y, Z);
}

    
void Particle::update() {
	float dt = ofGetLastFrameTime();
	integrer(dt);
	if (duration != -1.0f) {
		//on affiche la duration restante
		duration -= dt;
		if (duration < 0.0f) {
			//cas doit �tre g�r� par les classes contenant des listes de particules,
			//car si on "delete this", on ne peut plus it�rer sur la liste
			//car une particule de la liste n'existera pas (null error je suppose)
		}
	}
}

Vector Particle::getVelocity() {
	return _velocity;
}

void Particle::applyForce(float forceX, float forceY, float forceZ, float duration) {
	_forces.push_back(Force(Vector(forceX, forceY, forceZ), duration));
}

void Particle::bounce(Vector normal) {
	_velocity = _velocity - (normal * ((1+restitution) * _velocity.scalar_product(normal)));
	Vector tangent = _velocity - (normal * _velocity.scalar_product(normal));
	_velocity = tangent * friction + normal * _velocity.scalar_product(normal);
}

void Particle::integrer(float dt) {
	// On it�re sur les forces actives
	auto it = _forces.begin();
	while (it != _forces.end()) {
		Force& force = *it;
		float applicationTime = force.updateTimeElapsed(dt);

		_velocity += force.direction * _invertedMass * applicationTime;

		if (applicationTime != dt) {
			it = _forces.erase(it); // Suppression de la force si sa dur�e est termin�e
		}
		else {
			++it; // Element suivant
		}
	}

	// On met � jour la position
	_position += (_velocity * dt);
}
