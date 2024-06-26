﻿#include "Collision.h"

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
	if (_object1->getType() == 0 && _object2->getType() == 0) {
		resolveParticleToParticleCollisions(_object1->getParticle(), _object2->getParticle());
		return;
	}

	if (_object1->getType() == 1 && _object2->getType() == 1) {
		resolveCorpsRigideToCorpsRigideCollisions(_object1->getCorpsRigide(), _object2->getCorpsRigide());
		return;
	}

	if (_object1->getType() == 0 && _object2->getType() == 1) {
		resolveParticleToCorpsRigideCollisions(_object1->getParticle(), _object2->getCorpsRigide());
		return;
	}

	if (_object1->getType() == 1 && _object2->getType() == 0) {
		resolveParticleToCorpsRigideCollisions(_object2->getParticle(), _object1->getCorpsRigide());
		return;
	}
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
				if (point.x() != INFINITY ) {
					points.push_back(point);
					normals.push_back(face.normal());
					penetrations.push_back(intersection.penetration());

					// Debug
					debugCollisions.push_back(point);
					debugCollisionsNormals.push_back(face.normal());
				}
			}
		}
	}

	if (points.size() == 0) {
		return CollisionData();
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
	if (normal == Vector()) {
		normal = normals[0];
	}
	else {
		normal /= normals.size();
	}
	normal = normal.normalize();

	// Calcul de la pénétration (minimum des pénétrations non nulles, imprécis)

	double penetration = 0;

	for (double p : penetrations) {
		if (penetration != 0)
			penetration = min(penetration, p);
	}

	// Création de la collision

	return CollisionData(_object1, _object2, normal, point, penetration);
}

// Particle to Particle

void Collision::detectParticleToParticleCollisions(Particle* particle1, Particle* particle2)
{
}

void Collision::resolveParticleToParticleCollisions(Particle* particle1, Particle* particle2)
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

	if (!(collisionData1.isColliding() || collisionData2.isColliding())) {
		// Pas de collision
		return;
	}

	// Association des deux intersections

	Vector meanPosition = (collisionData1.point() + collisionData2.point()) / 2;
	Vector meanNormal = collisionData1.normal();
	if (collisionData1.normal() != collisionData2.normal()) {
		meanNormal = (collisionData1.normal() - collisionData2.normal()).normalize();
	}
	double meanPenetration = (collisionData1.penetration() + collisionData2.penetration());

	if (isnan(meanNormal.x())) {
		throw "Erreur de normal";
		return;
	}

	_collisionData = CollisionData(_object1, _object2, meanNormal, meanPosition, meanPenetration);
}

void Collision::resolveCorpsRigideToCorpsRigideCollisions(CorpsRigide* corpsRigide1, CorpsRigide* corpsRigide2)
{
	if (isnan(_collisionData.normal().x())) {
		throw "Erreur de normal";
		return;
	}

	// Offset en fonction de la masse
	double totalMass = corpsRigide1->centreMasse->getMass() + corpsRigide2->centreMasse->getMass();
	double offset1 = corpsRigide2->centreMasse->getMass() / totalMass;
	double offset2 = corpsRigide1->centreMasse->getMass() / totalMass;

	Vector penetrationVector = _collisionData.normal() * _collisionData.penetration();

	corpsRigide1->centreMasse->setPos(corpsRigide1->centreMasse->getPosition() + penetrationVector * offset1);
	corpsRigide2->centreMasse->setPos(corpsRigide2->centreMasse->getPosition() - penetrationVector * offset2);


	// Calcul de la vitesse relative au point de collision
	Vector relativeVelocity = corpsRigide1->getPunctualVelocity(_collisionData.point()) - corpsRigide2->getPunctualVelocity(_collisionData.point());

	// Debug
	Vector v1 = corpsRigide1->getPunctualVelocity(_collisionData.point());
	Vector v2 = corpsRigide2->getPunctualVelocity(_collisionData.point());

	// Calcul de la vitesse relative selon la normale
	double relativeVelocityNormal = relativeVelocity.scalar_product(_collisionData.normal());

	// Coefficient de restitution
	double restitution = corpsRigide1->centreMasse->restitution * corpsRigide2->centreMasse->restitution;

	// Calcul de la masse inverse incluant le moment d'inertie
	double momentInv1 = _collisionData.normal().scalar_product(
		corpsRigide1->inverseMomentOfInertia.produit(_collisionData.point()
		- corpsRigide1->centreMasse->getPosition()).vectoriel(_collisionData.normal()));

	double massInv1 = corpsRigide1->centreMasse->invertedMass + momentInv1;

	double momentInv2 = _collisionData.normal().scalar_product(
		corpsRigide2->inverseMomentOfInertia.produit(_collisionData.point()
		- corpsRigide2->centreMasse->getPosition()).vectoriel(_collisionData.normal()));


	double massInv2 = corpsRigide2->centreMasse->invertedMass + momentInv2;

	// Calcul de la magnitude de l'impulsion
	double magnitude = (1.0f + restitution) * relativeVelocityNormal / (massInv1 + massInv2);

	// Répartition de l'impulsion sur les deux objets
	double impulse1 = -magnitude;
	double impulse2 = magnitude;

	// Debug
	//corpsRigide1->centreMasse->setVelocity(Vector());
	//corpsRigide2->centreMasse->setVelocity(Vector());

	// Application de l'impulsion
	corpsRigide1->centreMasse->setVelocity(corpsRigide1->centreMasse->getVelocity() + _collisionData.normal() * impulse1 * massInv1);
	corpsRigide2->centreMasse->setVelocity(corpsRigide2->centreMasse->getVelocity() + _collisionData.normal() * impulse2 * massInv2);

	// Calcul du torque
	Vector l1 = _collisionData.point() - corpsRigide1->centreMasse->getPosition();
	Vector l2 = _collisionData.point() - corpsRigide2->centreMasse->getPosition();

	Vector torque1 = l1.vectoriel(_collisionData.normal() * impulse1 * corpsRigide1->centreMasse->invertedMass);
	Vector torque2 = l2.vectoriel(_collisionData.normal() * impulse2 * corpsRigide2->centreMasse->invertedMass);

	// Application du torque pour mettre a jour la vitesse angulaire
	corpsRigide1->angularVelocity += torque1 * massInv1;
	corpsRigide2->angularVelocity += torque2 * massInv2;
}

// Particle to CorpsRigide

void Collision::detectParticleToCorpsRigideCollisions(Particle* particle, CorpsRigide* corpsRigide)
{
}

void Collision::resolveParticleToCorpsRigideCollisions(Particle* particle, CorpsRigide* corpsRigide)
{
}


