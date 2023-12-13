#include "CorpsRigide.h"
#include "Vector.h"
#include "Particle.h"
#include "ofMain.h"
#include "Force.h"
#include <cmath>

CorpsRigide::CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color) {
	this->centreMasse = centreMasse;
	this->demiAxes = demiAxes;
	this->color = color;
	this->angularVelocity = Vector(0, 0, 0);
	this->rotation = Quaternion(1, 0, 0, 0);
	this->rotationMatrix = rotation.getRotationMatrix();

	double m = centreMasse->getMass();
	inverseMomentOfInertia = Matrice3x3(
		0, 0, m * (2 * demiAxes.y()) * (2 * demiAxes.y()) + (2 * demiAxes.z()) * (2 * demiAxes.z()) / 12.0f,
		0, m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.z()) * (2 * demiAxes.z()) / 12.0f, 0,
		m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.y()) * (2 * demiAxes.y()) / 12.0f, 0, 0
	);

	boundingSphereRadius = sqrt(demiAxes.x() * demiAxes.x() + demiAxes.y() * demiAxes.y() + demiAxes.z() * demiAxes.z());
}

CorpsRigide::CorpsRigide(Particle* centreMasse, double height, double width, double depth, ofColor color)
	: CorpsRigide(centreMasse, Vector(height / 2, width / 2, depth / 2), color){}


void CorpsRigide::bounce(Vector normal) {
	//on peut ajuster ici
	centreMasse->bounce(normal);
}

void CorpsRigide::update() {
	double dt = ofGetLastFrameTime();

	integrer(dt);
	verticesUpdated = false;
}

void CorpsRigide::draw() {
	ofPushMatrix();  // Sauvegarde la matrice courante
	ofTranslate(centreMasse->_position.x(), centreMasse->_position.y(), centreMasse->_position.z());  // Translate au centre de masse
	ofApplyVisualRotation();  // Applique la rotation
	ofSetColor(color);
	ofNoFill();
	ofSetLineWidth(10);
	ofDrawBox(0, 0, 0, demiAxes.x() * 2, demiAxes.y() * 2, demiAxes.z() * 2);
	ofFill();
	ofPopMatrix();  // Restaure la matrice precedente


	// DEBUG POUR VOIR LES EDGES
	//array<Face, 6>* faces = getFaces();
	//for (Edge edge : *getEdges()) {
	//	Vector position = edge.position();
	//	Vector position2 = edge.position() + edge.normal() * edge.length();
	//	ofSetLineWidth(4);
	//	ofDrawLine(position.x(), position.y(), position.z(), position2.x(), position2.y(), position2.z());
	//	ofSetLineWidth(10);
	//}

	 //DEBUG POUR VOIR LES FACES
	for (Face face : *getFaces()) {
		Vector position = face.position();
		Vector position2 = face.position() + face.right() * face.length() + face.up() * face.height();
		ofSetLineWidth(4);
		ofDrawLine(position.x(), position.y(), position.z(), position2.x(), position2.y(), position2.z());
		ofSetLineWidth(10);
	}
}

void CorpsRigide::applyForceAtPosition(Force* force, Vector position) {
	centreMasse->applyForce(force);

	_forcesAtPosition.push_back(new ForceAtPosition(force, position));
}

void CorpsRigide::integrer(double dt) {
	// Integration des forces translationnelles sur le centre de masse
	centreMasse->integrer(dt);

	// Aligner le moment d'inertie avec la rotation
	inverseMomentOfInertia = rotationMatrix.produit(inverseMomentOfInertia).produit(rotationMatrix.transposer());

	// Integration des torques absolus
	auto it1 = _torques.begin();
	while (it1 != _torques.end()) {
		double applicationTime = (*it1)->updateTimeElapsed(dt);

		integrerTorque(**it1, dt);

		if (applicationTime >= (*it1)->remainingTime) {
			it1 = _torques.erase(it1);
		}
		else {
			++it1;
		}
	}


	// calcul et integration des torques correspondant aux forces ponctuelles
	auto it2 = _forcesAtPosition.begin();
	while (it2 != _forcesAtPosition.end()) {
		double applicationTime = (*it2)->force->updateTimeElapsed(dt);

		// Calcul du torque
		Vector l = (*it2)->position - centreMasse->_position;
		Vector f = (*it2)->force->value();
		Vector torque = l.vectoriel(f);

		// Ajout du torque a la liste temporaire des torques
		integrerTorque(Torque(this, torque, (*it2)->force->remainingTime), dt);

		// Suppression de la force ponctuelle si sa duree est terminee
		if (applicationTime >= (*it2)->force->remainingTime) {
			it2 = _forcesAtPosition.erase(it2);
		}
		else {
			++it2;
		}
	}

	// Int�gration de la vitesse angulaire sur la rotation
	rotation = computeNewRotation(rotation, angularVelocity, dt);
	rotation = rotation.normalize();

	// Mise � jour de la matrice de rotation
	rotationMatrix = rotation.getRotationMatrix();

		
}

void CorpsRigide::integrerTorque(Torque torque, double dt) {
	// Application du torque pour mettre a jour la vitesse angulaire
	angularVelocity += torque.torque * inverseMomentOfInertia * min(dt, torque.remainingTime);
}

Quaternion CorpsRigide::computeNewRotation(Quaternion q, Vector w, double dt) {
	Quaternion rotationChange = Quaternion(0, w) * q;
	rotationChange = (rotationChange / 2.0f) * dt;
	return q + rotationChange;
}

void CorpsRigide::setRotation(Quaternion quaternion) {
	this->rotation = quaternion;
}

array<Face, 6>* CorpsRigide::getFaces()
{
	if (!verticesUpdated)
		updateVertices();

	array<Face, 6> faces = {
		Face(vertices[4], normals[0], normals[3], demiAxes.y() * 2, demiAxes.z() * 2),
		Face(vertices[1], normals[1], normals[3], demiAxes.y() * 2, demiAxes.z() * 2),
		Face(vertices[0], normals[2], normals[1], demiAxes.x() * 2, demiAxes.z() * 2),
		Face(vertices[2], normals[3], normals[0], demiAxes.x() * 2, demiAxes.z() * 2),
		Face(vertices[0], normals[4], normals[3], demiAxes.y() * 2, demiAxes.x() * 2),
		Face(vertices[5], normals[5], normals[3], demiAxes.y() * 2, demiAxes.x() * 2),
	};

	return &faces;
}

array<Edge, 12>* CorpsRigide::getEdges()
{
	if (!verticesUpdated)
		updateVertices();

	array<Edge, 12> edges = {
		Edge(vertices[0], normals[1], demiAxes.x() * 2),
		Edge(vertices[0], normals[3], demiAxes.y() * 2),
		Edge(vertices[0], normals[5], demiAxes.z() * 2),

		Edge(vertices[2], normals[0], demiAxes.x() * 2),
		Edge(vertices[2], normals[2], demiAxes.y() * 2),
		Edge(vertices[2], normals[5], demiAxes.z() * 2),

		Edge(vertices[5], normals[0], demiAxes.x() * 2),
		Edge(vertices[5], normals[3], demiAxes.y() * 2),
		Edge(vertices[5], normals[4], demiAxes.z() * 2),

		Edge(vertices[7], normals[1], demiAxes.x() * 2),
		Edge(vertices[7], normals[2], demiAxes.y() * 2),
		Edge(vertices[7], normals[4], demiAxes.z() * 2)
	};

	return &edges;
}

Vector CorpsRigide::getPunctualVelocity(Vector point)
{
	return centreMasse->getVelocity() + angularVelocity.vectoriel(point - centreMasse->_position);
}

Vector CorpsRigide::applyCorpsRotationToVector(Vector vector)
{
	return rotationMatrix.produit(vector);
}

void CorpsRigide::updateVertices()
{
	Vector position = centreMasse->getPosition();

	vertices[0] = position + applyCorpsRotationToVector(Vector(-demiAxes.x(), -demiAxes.y(), -demiAxes.z()));
	vertices[1] = position + applyCorpsRotationToVector(Vector(demiAxes.x(), -demiAxes.y(), -demiAxes.z()));
	vertices[2] = position + applyCorpsRotationToVector(Vector(demiAxes.x(), demiAxes.y(), -demiAxes.z()));
	vertices[3] = position + applyCorpsRotationToVector(Vector(-demiAxes.x(), demiAxes.y(), -demiAxes.z()));
	vertices[4] = position + applyCorpsRotationToVector(Vector(-demiAxes.x(), -demiAxes.y(), demiAxes.z()));
	vertices[5] = position + applyCorpsRotationToVector(Vector(demiAxes.x(), -demiAxes.y(), demiAxes.z()));
	vertices[6] = position + applyCorpsRotationToVector(Vector(demiAxes.x(), demiAxes.y(), demiAxes.z()));
	vertices[7] = position + applyCorpsRotationToVector(Vector(-demiAxes.x(), demiAxes.y(), demiAxes.z()));

	normals[0] = applyCorpsRotationToVector(Vector(-1, 0, 0));
	normals[1] = applyCorpsRotationToVector(Vector(1, 0, 0));
	normals[2] = applyCorpsRotationToVector(Vector(0, -1, 0));
	normals[3] = applyCorpsRotationToVector(Vector(0, 1, 0));
	normals[4] = applyCorpsRotationToVector(Vector(0, 0, -1));
	normals[5] = applyCorpsRotationToVector(Vector(0, 0, 1));

	verticesUpdated = true;
}

void CorpsRigide::ofApplyVisualRotation() {
	Vector visualRotation = this->rotationMatrix.getEuler();

	ofRotateZRad(visualRotation.z());
	ofRotateYRad(visualRotation.y());
	ofRotateXRad(visualRotation.x());
}

