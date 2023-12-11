#pragma once

#include <math.h>

#include "PhysicsObject.h"

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

