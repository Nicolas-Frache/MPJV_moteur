#include "Collision.h"

Collision::Collision(PhysicsObject* object1, PhysicsObject* object2)
{
	_object1 = object1;
	_object2 = object2;
}

void Collision::detect() {
	if (_object1->getType() == 0 && _object2->getType() == 0) {
		detectParticleToParticleCollisions(_object1->getParticle(), _object2->getParticle());
		return;
	}

	if (_object1->getType() == 1 && _object2->getType() == 1) {
		detectCorpsRigideToCorpsRigideCollisions(_object1->getCorpsRigide(), _object2->getCorpsRigide());
		return;
	}

	if (_object1->getType() == 0 && _object2->getType() == 1) {
		detectParticleToCorpsRigideCollisions(_object1->getParticle(), _object2->getCorpsRigide());
		return;
	}

	if (_object1->getType() == 1 && _object2->getType() == 0) {
		detectParticleToCorpsRigideCollisions(_object2->getParticle(), _object1->getCorpsRigide());
		return;
	}
}

void Collision::resolve()
{
}

CollisionData Collision::detectEdgesToFacesCollisions(vector<Edge> edges, vector<Face> faces)
{
	vector <Vector> points = vector<Vector>();
	vector <Vector> normals = vector<Vector>();
	vector <double> penetrations = vector<double>();

	for (Edge edge : edges) {
		for (Face face : faces) {
			if (edge.intersectsPlan(face)) {
				PositionAndPenetration intersection = edge.intersection(face);
				Vector point = intersection.position();
				if (point.x() != INFINITY) {
					points.push_back(point);
					normals.push_back(face.normal());
					penetrations.push_back(intersection.penetration());
				}
			}
		}
	}

	// Moyenne des points et des normales

	Vector point = Vector();
	Vector normal = Vector();

	for (const Vector &p : points) {
		point += p;
	}

	for (const Vector &n : normals) {
		normal += n;
	}

	point /= points.size();
	normal /= normals.size();
	normal = normal.normalize();

	// Calcul de la pénétration (moyenne des pénétrations, imprécis)

	double penetration = 0;

	for (double p : penetrations) {
		penetration += p;
	}

	penetration /= penetrations.size();

	// Création de la collision

	return CollisionData(_object1, _object2, normal, point, penetration);
}

// Particle to Particle

void Collision::detectParticleToParticleCollisions(Particle* particle1, Particle* particle2)
{
}

void Collision::resolveParticleToParticleCollisions(Particle* particle1, Particle* particle2, CollisionData collisionData)
{
}

// CorpsRigide to CorpsRigide

void Collision::detectCorpsRigideToCorpsRigideCollisions(CorpsRigide* corpsRigide1, CorpsRigide* corpsRigide2)
{
	// Génération des faces et des arêtes à tester
	// (on ne teste que la moitié des arêtes et des faces qui se font face) → actuellement non, mais optimisation possible

	vector<Face> faces1 = vector<Face>();
	vector<Face> faces2 = vector<Face>();

	vector<Edge> edges1 = vector<Edge>();
	vector<Edge> edges2 = vector<Edge>();

	// Faces

	for (const Face &face : *corpsRigide1->getFaces()) {
		faces1.push_back(face);
	}

	for (const Face &face : *corpsRigide2->getFaces()) {
		faces2.push_back(face);
	}

	// Arêtes

	for (const Edge &edge : *corpsRigide1->getEdges()) {
		edges1.push_back(edge);
	}

	for (const Edge &edge : *corpsRigide2->getEdges()) {
		edges2.push_back(edge);
	}

	// Test des collisions

	CollisionData collisionData1 = detectEdgesToFacesCollisions(edges1, faces2);
	CollisionData collisionData2 = detectEdgesToFacesCollisions(edges2, faces1);

	// Association des deux collisions

	Vector meanPosition = (collisionData1.point() + collisionData2.point()) / 2;
	Vector meanNormal = (collisionData1.normal() - collisionData2.normal()).normalize();
	double meanPenetration = (collisionData1.penetration() + collisionData2.penetration());

	_collisionData = CollisionData(_object1, _object2, meanNormal, meanPosition, meanPenetration);
}

void Collision::resolveCorpsRigideToCorpsRigideCollisions(CorpsRigide* corpsRigide1, CorpsRigide* corpsRigide2, CollisionData collisionData)
{
}

// Particle to CorpsRigide

void Collision::detectParticleToCorpsRigideCollisions(Particle* particle, CorpsRigide* corpsRigide)
{
}

void Collision::resolveParticleToCorpsRigideCollisions(Particle* particle, CorpsRigide* corpsRigide, CollisionData collisionData)
{
}


