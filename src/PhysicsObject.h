#pragma once

#include "Particle.h"
#include "CorpsRigide.h"

class PhysicsObject
{
public:
	PhysicsObject(Particle* particle);
	PhysicsObject(CorpsRigide* corpsRigide);

	Vector getPos();
	int getType() const { return _type; }
	Particle* getParticle() { return _particle; }
	CorpsRigide* getCorpsRigide() { return _corpsRigide; }
	double getRadius();

	static void resetId() { _nextId = -1; _objects = vector<PhysicsObject*>(); }
	int getId() { return _id; }
	static int getLastId() { return _nextId; }
	static PhysicsObject* getObjectById(int id) { return _objects[id]; }
	static vector<PhysicsObject*>* getObjectsVector() { return &_objects; }

private:
	static vector<PhysicsObject*> _objects;
	static int _nextId;
	int _id;
	int _type; // 0 = particle, 1 = corpsRigide
	Particle* _particle;
	CorpsRigide* _corpsRigide;
	static Particle defaultPart;
	static CorpsRigide defaultCorps;
};

