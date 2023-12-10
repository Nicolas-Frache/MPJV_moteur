#pragma once

#include <math.h>

#include "Particle.h"
#include "CorpsRigide.h"

class PhysicsObject
{
	public:
		PhysicsObject(Particle* particle) { this->particle = particle; this->type = 0; }
		PhysicsObject(CorpsRigide* corpsRigide) { this->corpsRigide = corpsRigide; this->type = 1; }

		Vector getPos() { if (type == 0) return particle->position; else return corpsRigide->centreMasse->position; }
		int getType() const { return type; }
		Particle* getParticle() { return particle; }
		CorpsRigide* getCorpsRigide() { return corpsRigide; }
		double getRadius() { if (type == 0) return particle->radius; else return corpsRigide->boundingSphereRadius; }

	private:
		int type; // 0 = particle, 1 = corpsRigide
		Particle* particle;
		CorpsRigide* corpsRigide;
};


class OcTree
{
	public:
		OcTree(vector<PhysicsObject*>* objects, int maxObjects, int maxDepth);
		OcTree(vector<PhysicsObject*>* objects, Vector centre, double size, int maxObjects, int maxDepth);

		int getDepth();
		double getSize() { return size; }
		Vector getCentre() { return centre; }

		vector<vector<PhysicsObject*>> getPossibleCollisions();

		string toString();
		void draw();

	private:
		Vector centre;
		double size;
		Vector minCoord;
		Vector maxCoord;
		vector<PhysicsObject*> objects;
		double minRadius = INFINITY;				// Plus petit rayon d'un objet trouve dans l'octree
		int maxObjects;
		int maxDepth;
		OcTree* children[8];
		bool hasChildren = false;

		void computeMinMax();
		bool objectInBound(PhysicsObject* object);
		void checkSplitNeeded();
		void split();

};

