#include "Laser.h"
#include "../MPJV_moteur/src/Particle.h"

Laser::Laser(float X1, float Y1, float Z1, float X2, float Y2, float Z2, float invertedMass, ofColor color)
	: Particle(X1, Y1, Z1, invertedMass, color) {

	_startPoint.set(X1, Y1, Z1);
	_endPoint.set(X2, Y2, Z2);
}

void Laser::setStartPoint(Vector startPoint) {
	_startPoint = startPoint;
}

void Laser::setEndPoint(Vector endPoint) {
	_endPoint = endPoint;
}

void Laser::setPos(Vector startPoint, Vector endPoint) {
	_startPoint = startPoint;
	_endPoint = endPoint;
}

void Laser::setMass(float invertedMass) {
	_invertedMass = invertedMass;
}

void Laser::setColor(ofColor color) {
	_color = color;
}

void Laser::setSize(float size) {
	_size = size;
}

void Laser::setVelocity(Vector velocity) {
	_velocity = velocity;
}

void Laser::setForce(Vector force) {
	_force = force;
}

Vector Laser::getStartPointPos() {
	return _startPoint;
}

Vector Laser::getEndPointPos() {
	return _endPoint;
}

float Laser::getInvMass() {
	return _invertedMass;
}

ofColor Laser::getColor() {
	return _color;
}

float Laser::getSize() {
	return _size;
}

Vector Laser::getVelocity() {
	return _velocity;
}

Vector Laser::getForce() {
	return _force;
}

void Laser::update() {
	_velocity += _force * _invertedMass;

	cout << "_startPoint: " << _startPoint << " endPoint : " << _endPoint << ", velocity : " << _velocity << ", force : " << _force << endl;

	_startPoint += _velocity;
	_endPoint += _velocity;

	cout << "_startPoint: " << _startPoint << " endPoint : " << _endPoint << ", velocity : " << _velocity << ", force : " << _force << endl;
	cout << "Adresse de monObjet Laser : " << this << std::endl;
}


void Laser::draw() {
	ofSetColor(getColor());
	ofDrawLine(_startPoint.x(), _startPoint.y(), _startPoint.z(), _endPoint.x(), _endPoint.y(), _endPoint.z());
}

void Laser::applyForce(float forceX, float forceY, float forceZ) {
	_force += Vector(forceX, forceY, forceZ);
}

void Laser::integrer(float dt) {
	_velocity += _force * _invertedMass * dt;
	_startPoint += _velocity * dt;
	_endPoint += _velocity * dt;
	_force = Vector(0, 0, 0);
}