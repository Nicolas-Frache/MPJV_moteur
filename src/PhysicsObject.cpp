#include "PhysicsObject.h"

int PhysicsObject::_nextId = -1;
vector<PhysicsObject*> PhysicsObject::_objects = vector<PhysicsObject*>();
Particle PhysicsObject::defaultPart = Particle(Vector(0, 0, 0), 0, ofColor::black, 0);
CorpsRigide PhysicsObject::defaultCorps = CorpsRigide(&Particle(Vector(0, 0, 0), 0, ofColor::black, 0), Vector(0, 0, 0), ofColor::black);

PhysicsObject::PhysicsObject(Particle* particle)
{
	_particle = particle;
	_type = 0;
	_id = ++_nextId;
	_objects.push_back(this);

	// Sert uniquement � initialiser la variable _corpsRigide, n'est pas utilis�
	_corpsRigide = &defaultCorps;
}

PhysicsObject::PhysicsObject(CorpsRigide* corpsRigide)
{
	_corpsRigide = corpsRigide;
	_type = 1;
	_id = ++_nextId;
	_objects.push_back(this);

	// Sert uniquement � initialiser la variable _particle, n'est pas utilis�
	_particle = &defaultPart;
}


Vector PhysicsObject::getPos() {
	if (_type == 0)
		return _particle->position;
	else
		return _corpsRigide->centreMasse->position;
}

double PhysicsObject::getRadius() {
	if (_type == 0)
		return _particle->radius;
	else
		return _corpsRigide->boundingSphereRadius;
}

