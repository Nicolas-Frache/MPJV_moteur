#include "OcTree.h"


OcTree::OcTree(vector<PhysicsObject*>* objects, int maxObjects, int maxDepth)
{
	this->objects = vector<PhysicsObject*>(); // Copy objects
	for (PhysicsObject* object : *objects) {
		this->objects.push_back(object);
		if (object->getRadius() < minRadius) minRadius = object->getRadius();
	}

	this->maxObjects = maxObjects;
	this->maxDepth = maxDepth;

	// Find centre and size
	double minX = 0;
	double maxX = 0;
	double minY = 0;
	double maxY = 0;
	double minZ = 0;
	double maxZ = 0;

	for (PhysicsObject* object : this->objects) {
		Vector pos = object->getPos();
		if (pos.x() < minX) minX = pos.x() - 1;
		if (pos.x() > maxX) maxX = pos.x() + 1;
		if (pos.y() < minY) minY = pos.y() - 1;
		if (pos.y() > maxY) maxY = pos.y() + 1;
		if (pos.z() < minZ) minZ = pos.z() - 1;
		if (pos.z() > maxZ) maxZ = pos.z() + 1;
	}									// ↑ marge de sécurité

	double x = (minX + maxX) / 2;
	double y = (minY + maxY) / 2;
	double z = (minZ + maxZ) / 2;

	double sizeX = maxX - minX;
	double sizeY = maxY - minY;
	double sizeZ = maxZ - minZ;

	double size = max(sizeX, max(sizeY, sizeZ));

	this->centre = Vector(x, y, z);
	this->size = size;

	computeMinMax();
	checkSplitNeeded();
}

OcTree::OcTree(vector<PhysicsObject*>* objects, Vector centre, double size, int maxObjects, int maxDepth)
{
	this->centre = centre;
	this->size = size;
	this->maxObjects = maxObjects;
	this->maxDepth = maxDepth;
	computeMinMax();

	this->objects = vector<PhysicsObject*>(); // Copy objects
	for (PhysicsObject* object : *objects) {
		if (objectInBound(object)) {
			this->objects.push_back(object);
			if (object->getRadius() < minRadius) minRadius = object->getRadius();
		}
	}

	checkSplitNeeded();
}

void OcTree::computeMinMax()
{
	double x = centre.x();
	double y = centre.y();
	double z = centre.z();

	double demiSize = this->size / 2;

	minCoord = Vector(x - demiSize, y - demiSize, z - demiSize);
	maxCoord = Vector(x + demiSize, y + demiSize, z + demiSize);
}

bool OcTree::objectInBound(PhysicsObject* object)
{
	Vector pos = object->getPos();
	double radius = object->getRadius();

	if (pos.x() + radius < minCoord.x()) return false;
	if (pos.x() - radius > maxCoord.x()) return false;
	if (pos.y() + radius < minCoord.y()) return false;
	if (pos.y() - radius > maxCoord.y()) return false;
	if (pos.z() + radius < minCoord.z()) return false;
	if (pos.z() - radius > maxCoord.z()) return false;

	return true;
}

void OcTree::checkSplitNeeded()
{
	if (objects.size() <= maxObjects) return;
	if (maxDepth == 0) return;
	if (size < minRadius * 2) return;

	split();
}

void OcTree::split()
{
	double semiSize = this->size / 2;
	double quarterSize = this->size / 4;

	Vector centre0 = Vector(centre.x() - quarterSize, centre.y() - quarterSize, centre.z() - quarterSize);
	Vector centre1 = Vector(centre.x() + quarterSize, centre.y() - quarterSize, centre.z() - quarterSize);
	Vector centre2 = Vector(centre.x() - quarterSize, centre.y() + quarterSize, centre.z() - quarterSize);
	Vector centre3 = Vector(centre.x() + quarterSize, centre.y() + quarterSize, centre.z() - quarterSize);
	Vector centre4 = Vector(centre.x() - quarterSize, centre.y() - quarterSize, centre.z() + quarterSize);
	Vector centre5 = Vector(centre.x() + quarterSize, centre.y() - quarterSize, centre.z() + quarterSize);
	Vector centre6 = Vector(centre.x() - quarterSize, centre.y() + quarterSize, centre.z() + quarterSize);
	Vector centre7 = Vector(centre.x() + quarterSize, centre.y() + quarterSize, centre.z() + quarterSize);

	children[0] = new OcTree(&objects, centre0, semiSize, maxObjects, maxDepth - 1);
	children[1] = new OcTree(&objects, centre1, semiSize, maxObjects, maxDepth - 1);
	children[2] = new OcTree(&objects, centre2, semiSize, maxObjects, maxDepth - 1);
	children[3] = new OcTree(&objects, centre3, semiSize, maxObjects, maxDepth - 1);
	children[4] = new OcTree(&objects, centre4, semiSize, maxObjects, maxDepth - 1);
	children[5] = new OcTree(&objects, centre5, semiSize, maxObjects, maxDepth - 1);
	children[6] = new OcTree(&objects, centre6, semiSize, maxObjects, maxDepth - 1);
	children[7] = new OcTree(&objects, centre7, semiSize, maxObjects, maxDepth - 1);

	hasChildren = true;
}

int OcTree::getDepth()
{
	if (hasChildren) {
		int maxDepth = 0;
		for (int i = 0; i < 8; ++i) {
			int depth = children[i]->getDepth();
			if (depth > maxDepth) maxDepth = depth;
		}
		return maxDepth + 1;
	}
	else {
		return 1;
	}
}

vector<vector<PhysicsObject*>> OcTree::getPossibleCollisions()
{
	vector<vector<PhysicsObject*>> collisions = vector<vector<PhysicsObject*>>();

	if (hasChildren) {
		for (int i = 0; i < 8; i++) {
			vector<vector<PhysicsObject*>> childCollisions = children[i]->getPossibleCollisions();
			for (vector<PhysicsObject*> collision : childCollisions) {
				collisions.push_back(collision);
			}
			// Cas problematique, deux objets sur la meme frontiere
		}
	}
	else {
		for (int i = 0; i < objects.size(); i++) {
			for (int j = i + 1; j < objects.size(); j++) {
				vector<PhysicsObject*> collision = vector<PhysicsObject*>();
				collision.push_back(objects[i]);
				collision.push_back(objects[j]);
				collisions.push_back(collision);
			}
		}
	}

	return collisions;
}

string OcTree::toString()
{
	string str = "";
	if (hasChildren) {
		for (int i = 0; i < 8; i++) {
			str += "(" + children[i]->toString() + ")";
		}
	}
	else {
		str += to_string(objects.size());
	}
	return str;
}

void OcTree::draw()
{
	ofSetColor(ofColor::red);
	ofNoFill();
	ofSetLineWidth(1);
	ofDrawBox(centre.x(), centre.y(), centre.z(), size, size, size);
	ofFill();

	if (hasChildren) {
		for (int i = 0; i < 8; i++) {
			children[i]->draw();
		}
	}
}