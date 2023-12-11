#include "OcTree.h"

int PhysicsObject::nextId = -1;

OcTree::OcTree(vector<PhysicsObject*>* objects, int maxObjects, int maxDepth, vector<set<int>>* potentialCollisionList)
{
	_objects = vector<PhysicsObject*>(); // Copy objects
	for (PhysicsObject* object : *objects) {
		_objects.push_back(object);
		if (object->getRadius() < _minRadius) _minRadius = object->getRadius();
	}

	_maxObjects = maxObjects;
	_maxDepth = maxDepth;

	// Find centre and size
	double minX = 0;
	double maxX = 0;
	double minY = 0;
	double maxY = 0;
	double minZ = 0;
	double maxZ = 0;

	for (PhysicsObject* object : this->_objects) {
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

	_centre = Vector(x, y, z);
	_size = size;
	_potentialCollisionList = potentialCollisionList;

	computeMinMax();
	checkSplitNeeded();
}

OcTree::OcTree(vector<PhysicsObject*>* objects, Vector centre, double size, int maxObjects, int maxDepth, vector<set<int>>* potentialCollisionList)
{
	_centre = centre;
	_size = size;
	_maxObjects = maxObjects;
	_maxDepth = maxDepth;
	_potentialCollisionList = potentialCollisionList;
	computeMinMax();

	_objects = vector<PhysicsObject*>(); // Copy objects
	for (PhysicsObject* object : *objects) {
		if (objectInBound(object)) {
			_objects.push_back(object);
			if (object->getRadius() < _minRadius) _minRadius = object->getRadius();
		}
	}

	checkSplitNeeded();
}

void OcTree::computeMinMax()
{
	double x = _centre.x();
	double y = _centre.y();
	double z = _centre.z();

	double demiSize = this->_size / 2;

	_minCoord = Vector(x - demiSize, y - demiSize, z - demiSize);
	_maxCoord = Vector(x + demiSize, y + demiSize, z + demiSize);
}

bool OcTree::objectInBound(PhysicsObject* object)
{
	Vector pos = object->getPos();
	double radius = object->getRadius();

	if (pos.x() + radius < _minCoord.x()) return false;
	if (pos.x() - radius > _maxCoord.x()) return false;
	if (pos.y() + radius < _minCoord.y()) return false;
	if (pos.y() - radius > _maxCoord.y()) return false;
	if (pos.z() + radius < _minCoord.z()) return false;
	if (pos.z() - radius > _maxCoord.z()) return false;

	return true;
}

void OcTree::checkSplitNeeded()
{
	if (_objects.size() <= _maxObjects) return;
	if (_maxDepth == 0) return;
	if (_size < _minRadius * 2) return;		// Inutile de subdiviser si tous les objets sont plus grands que la taille de la cellule

	split();
}

void OcTree::split()
{
	double semiSize = this->_size / 2;
	double quarterSize = this->_size / 4;

	Vector centre0 = Vector(_centre.x() - quarterSize, _centre.y() - quarterSize, _centre.z() - quarterSize);
	Vector centre1 = Vector(_centre.x() + quarterSize, _centre.y() - quarterSize, _centre.z() - quarterSize);
	Vector centre2 = Vector(_centre.x() - quarterSize, _centre.y() + quarterSize, _centre.z() - quarterSize);
	Vector centre3 = Vector(_centre.x() + quarterSize, _centre.y() + quarterSize, _centre.z() - quarterSize);
	Vector centre4 = Vector(_centre.x() - quarterSize, _centre.y() - quarterSize, _centre.z() + quarterSize);
	Vector centre5 = Vector(_centre.x() + quarterSize, _centre.y() - quarterSize, _centre.z() + quarterSize);
	Vector centre6 = Vector(_centre.x() - quarterSize, _centre.y() + quarterSize, _centre.z() + quarterSize);
	Vector centre7 = Vector(_centre.x() + quarterSize, _centre.y() + quarterSize, _centre.z() + quarterSize);

	_children[0] = new OcTree(&_objects, centre0, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[1] = new OcTree(&_objects, centre1, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[2] = new OcTree(&_objects, centre2, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[3] = new OcTree(&_objects, centre3, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[4] = new OcTree(&_objects, centre4, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[5] = new OcTree(&_objects, centre5, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[6] = new OcTree(&_objects, centre6, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);
	_children[7] = new OcTree(&_objects, centre7, semiSize, _maxObjects, _maxDepth - 1, _potentialCollisionList);

	_hasChildren = true;
}

int OcTree::getDepth()
{
	if (_hasChildren) {
		int maxDepth = 0;
		for (int i = 0; i < 8; ++i) {
			int depth = _children[i]->getDepth();
			if (depth > maxDepth) maxDepth = depth;
		}
		return maxDepth + 1;
	}
	else {
		return 1;
	}
}

void OcTree::getPossibleCollisions()
{
	vector<vector<PhysicsObject*>> collisions = vector<vector<PhysicsObject*>>();

	if (_hasChildren) {
		for (int i = 0; i < 8; ++i) {
			_children[i]->getPossibleCollisions();
		}
	}
	else {
		for (int i = 0; i < _objects.size(); ++i) {
			for (int j = i + 1; j < _objects.size(); ++j) {
				_potentialCollisionList->at(_objects[i]->getId()).insert(_objects[j]->getId());
			}
		}
	}
}

string OcTree::toString()
{
	string str = "";
	if (_hasChildren) {
		for (int i = 0; i < 8; ++i) {
			str += "(" + _children[i]->toString() + ")";
		}
	}
	else {
		str += to_string(_objects.size());
	}
	return str;
}

void OcTree::draw()
{
	ofSetColor(ofColor::red);
	ofNoFill();
	ofSetLineWidth(1);
	ofDrawBox(_centre.x(), _centre.y(), _centre.z(), _size, _size, _size);
	ofFill();

	if (_hasChildren) {
		for (int i = 0; i < 8; ++i) {
			_children[i]->draw();
		}
	}
}