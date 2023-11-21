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
	this->rotationMatrix.setIdentity();

	float m = centreMasse->getMass();
	inverseMomentOfInertia = Vector(
		1 / (1 / 12.0f * m * (2 * demiAxes.y()) * (2 * demiAxes.y()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.y()) * (2 * demiAxes.y()))
	);
}

CorpsRigide::CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color) {
	this->centreMasse = centreMasse;
	this->demiAxes = Vector(height / 2, width / 2, depth / 2);
	this->color = color;
	this->rotationMatrix.setIdentity();

	float m = centreMasse->getInvMass();
	inverseMomentOfInertia = Vector(
		1 / (1 / 12.0f * m * (2 * demiAxes.y()) * (2 * demiAxes.y()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.z()) * (2 * demiAxes.z())),
		1 / (1 / 12.0f * m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.y()) * (2 * demiAxes.y()))
	);
}

void CorpsRigide::applyForce(Vector force, float duration) {
	centreMasse->applyForce(force, duration);
}

void CorpsRigide::applyForce(float forceX, float forceY, float forceZ, float duration) {
	centreMasse->applyForce(forceX, forceY, forceZ, duration);
}

void CorpsRigide::applyForce(Force* force) {
	centreMasse->applyForce(force);
}

void CorpsRigide::applyTorque(Vector torque, float duration) {
	ForceRotationnelle* torqueForce = new ForceRotationnelle(this, torque, duration);
	_torques.push_back(torqueForce);
}

void CorpsRigide::applyTorque(float torqueX, float torqueY, float torqueZ, float duration) {
	applyTorque(Vector(torqueX, torqueY, torqueZ), duration);
}

void CorpsRigide::removeTorque(ForceRotationnelle* torque) {
	_torques.remove(torque);
}

void CorpsRigide::bounce(Vector normal) {
	//on peut ajuster ici
	centreMasse->bounce(normal);
}

void CorpsRigide::update() {
	float dt = ofGetLastFrameTime();

	integrer(dt);
	// on affiche la matrice de rotation :
	//rotationMatrix.afficher();

	Vector rotationChange = angularVelocity * dt;

	auto it = _torques.begin();
	while (it != _torques.end()) {
		float applicationTime = (*it)->updateTimeElapsed(dt);

		(*it)->applyTorque();

		// Suppression de la force rotationnelle si sa durée est terminée
		if (applicationTime >= (*it)->duration) {
			it = _torques.erase(it);
		}
		else {
			++it;
		}
	}

	// Utilisez la matrice modifiée ici
	Matrice4x4 rotationMatrixChange;
	rotationMatrixChange.setIdentity();
	rotationMatrixChange.rotateDeg(rotationChange.x(), 1, 0, 0);
	rotationMatrixChange.rotateDeg(rotationChange.y(), 0, 1, 0);
	rotationMatrixChange.rotateDeg(rotationChange.z(), 0, 0, 1);

	// Accumulez la rotation en multipliant la matrice actuelle par la matrice de rotation
	rotationMatrix = rotationMatrixChange.produit(rotationMatrix);

	centreMasse->update();
}

void CorpsRigide::draw() {
	ofPushMatrix();  // Sauvegarde la matrice courante
	ofApplyRotation();  // Applique la rotation
	ofSetColor(color);
	ofDrawBox(centreMasse->position.x(), centreMasse->position.y(), centreMasse->position.z(), demiAxes.x(), demiAxes.y(), demiAxes.z());
	ofPopMatrix();  // Restaure la matrice précédente
}

void CorpsRigide::integrer(float dt) {
	// Intégration des forces translationnelles sur le centre de masse
	centreMasse->integrer(dt);

	// Intégration des torques sur le moment d'inertie
	auto it = _torques.begin();
	while (it != _torques.end()) {
		float applicationTime = (*it)->updateTimeElapsed(dt);

		// Application du torque pour mettre à jour la vitesse angulaire
		angularVelocity += (*it)->torque.mult_by_component(inverseMomentOfInertia) * applicationTime;

		// Suppression de la force rotationnelle si sa durée est terminée
		if (applicationTime >= (*it)->duration) {
			it = _torques.erase(it);
		}
		else {
			++it;
		}
	}
}

void CorpsRigide::setRotationMatrix(Matrice4x4 matrix) {
	this->rotationMatrix = matrix;
}

//void CorpsRigide::setRotationMatrix(Quaternion quaternion) {
//	this->rotationMatrix = quaternion.toMatrix();
//}

void CorpsRigide::ofApplyRotation() {
	Vector rotation = rotationMatrix.getEuler();
	cout << "rotation euler: " << rotation << endl;
	ofRotateXDeg((rotation.x()));
	ofRotateYDeg((rotation.y()));
	ofRotateZDeg((rotation.z()));
}

void CorpsRigide::applyRotation(Vector rotationChange) {
	Matrice4x4 rotationMatrixChange;
	rotationMatrixChange.setIdentity();
	rotationMatrixChange.rotateDeg((rotationChange.x()), 1, 0, 0);
	rotationMatrixChange.rotateDeg((rotationChange.y()), 0, 1, 0);
	rotationMatrixChange.rotateDeg((rotationChange.z()), 0, 0, 1);

	// Multipliez la matrice actuelle par la nouvelle matrice de rotation
	rotationMatrix = rotationMatrixChange.produit(rotationMatrix);
}

float CorpsRigide::normalizeAngle(float angle) {
	while (angle > PI) {
		angle -= 2.0 * PI;
	}
	while (angle <= -PI) {
		angle += 2.0 * PI;
	}
	return angle;
}