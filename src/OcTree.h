#pragma once

#include <math.h>

#include "Particle.h"
#include "CorpsRigide.h"

class PhysicsObject
{
	public:
		PhysicsObject(Particle* particle) { this->particle = particle; this->type = 0; id = ++nextId; }
		PhysicsObject(CorpsRigide* corpsRigide) { this->corpsRigide = corpsRigide; this->type = 1; id = ++nextId; }

		Vector getPos() { if (type == 0) return particle->position; else return corpsRigide->centreMasse->position; }
		int getType() const { return type; }
		Particle* getParticle() { return particle; }
		CorpsRigide* getCorpsRigide() { return corpsRigide; }
		double getRadius() { if (type == 0) return particle->radius; else return corpsRigide->boundingSphereRadius; }

		static void resetId() { nextId = -1; }
		int getId() { return id; }
		static int getLastId() { return nextId; }

	private:
		static int nextId;
		int id;
		int type; // 0 = particle, 1 = corpsRigide
		Particle* particle;
		CorpsRigide* corpsRigide;
};


class OcTree
{
	public:
		OcTree(vector<PhysicsObject*>* objects, int maxObjects, int maxDepth, vector<set<int>>* potentialCollisionList);
		OcTree(vector<PhysicsObject*>* objects, Vector centre, double size, int maxObjects, int maxDepth, vector<set<int>>* potentialCollisionList);

		int getDepth();
		double getSize() { return _size; }
		Vector getCentre() { return _centre; }

		void getPossibleCollisions();

		string toString();
		void draw();

	private:
		Vector _centre;
		double _size;
		Vector _minCoord;
		Vector _maxCoord;
		vector<PhysicsObject*> _objects;
		vector<set<int>>* _potentialCollisionList;
		double _minRadius = INFINITY;				// Plus petit rayon d'un objet trouve dans l'octree
		int _maxObjects;
		int _maxDepth;
		OcTree* _children[8];
		bool _hasChildren = false;

		void computeMinMax();
		bool objectInBound(PhysicsObject* object);
		void checkSplitNeeded();
		void split();

};

