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

	float m = centreMasse->getMass();
	inverseMomentOfInertia = Matrice3x3(
		0, 0, m * (2 * demiAxes.y()) * (2 * demiAxes.y()) + (2 * demiAxes.z()) * (2 * demiAxes.z()) / 12.0f,
		0, m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.z()) * (2 * demiAxes.z()) / 12.0f, 0,
		m * (2 * demiAxes.x()) * (2 * demiAxes.x()) + (2 * demiAxes.y()) * (2 * demiAxes.y()) / 12.0f, 0, 0
	);
}

CorpsRigide::CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color)
	: CorpsRigide(centreMasse, Vector(height / 2, width / 2, depth / 2), color){}


void CorpsRigide::bounce(Vector normal) {
	//on peut ajuster ici
	centreMasse->bounce(normal);
}

void CorpsRigide::update() {
	float dt = ofGetLastFrameTime();

	integrer(dt);

}

void CorpsRigide::draw() {
	ofPushMatrix();  // Sauvegarde la matrice courante
	ofTranslate(centreMasse->position.x(), centreMasse->position.y(), centreMasse->position.z());  // Translate au centre de masse
	ofApplyVisualRotation();  // Applique la rotation
	ofSetColor(color);
	ofNoFill();
	ofSetLineWidth(10);
	ofDrawBox(0, 0, 0, demiAxes.x(), demiAxes.y(), demiAxes.z());
	ofFill();
	ofPopMatrix();  // Restaure la matrice pr�c�dente
}

void CorpsRigide::integrer(float dt) {
	// Int�gration des forces translationnelles sur le centre de masse
	centreMasse->integrer(dt);

	// Aligner le moment d'inertie avec la rotation
	inverseMomentOfInertia = rotationMatrix.produit(inverseMomentOfInertia).produit(rotationMatrix.transposer());

	// Int�gration des torques sur le moment d'inertie
	auto it = _torques.begin();
	while (it != _torques.end()) {
		float applicationTime = (*it)->updateTimeElapsed(dt);

		// Application du torque pour mettre � jour la vitesse angulaire
		angularVelocity += (*it)->torque * inverseMomentOfInertia * dt;

		// Suppression de la force rotationnelle si sa dur�e est termin�e
		if (applicationTime >= (*it)->duration) {
			it = _torques.erase(it);
		}
		else {
			++it;
		}
	}

	// Int�gration de la vitesse angulaire sur la rotation
	rotation = computeNewRotation(rotation, angularVelocity, dt);

	// Mise � jour de la matrice de rotation
	rotationMatrix = rotation.getRotationMatrix();
}

Quaternion CorpsRigide::computeNewRotation(Quaternion q, Vector w, float dt) {
	Quaternion rotationChange = Quaternion(0, w.x(), w.y(), w.z()) * q;
	rotationChange = rotationChange / 2.0f * dt;
	return q + rotationChange;
}

void CorpsRigide::setRotation(Quaternion quaternion) {
	this->rotation = quaternion;
}


void CorpsRigide::ofApplyVisualRotation() {
	Vector rotation = this->rotationMatrix.getEuler();

	ofRotateZRad(rotation.z());
	ofRotateYRad(rotation.y());
	ofRotateXRad(rotation.x());
}
