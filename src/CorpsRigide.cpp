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
	ofPopMatrix();  // Restaure la matrice precedente
}

void CorpsRigide::applyForceAtPosition(Force* force, Vector position) {
	centreMasse->applyForce(force);

	_forcesAtPosition.push_back(new ForceAtPosition(force, position));
}

void CorpsRigide::integrer(double dt) {
	// Liste temporaire des torques
	list<Torque*> tempTorques = list<Torque*>();
	tempTorques.assign(_torques.begin(), _torques.end());

	// Ajout des torques correspondant aux forces ponctuelles
	auto it0 = _forcesAtPosition.begin();
	while (it0 != _forcesAtPosition.end()) {
		double applicationTime = (*it0)->force->updateTimeElapsed(dt);

		// Calcul du torque
		Vector l = (*it0)->position - centreMasse->position;
		Vector f = (*it0)->force->value();
		Vector torque = l.vectoriel(f);

		// Ajout du torque a la liste temporaire des torques
		tempTorques.push_back(new Torque(this, torque, applicationTime));

		// Suppression de la force ponctuelle si sa duree est terminee
		if (applicationTime >= (*it0)->force->timeRemaining) {
			it0 = _forcesAtPosition.erase(it0);
		}
		else {
			++it0;
		}
	}

	// Integration des forces translationnelles sur le centre de masse
	centreMasse->integrer(dt);

	// Aligner le moment d'inertie avec la rotation
	inverseMomentOfInertia = rotationMatrix.produit(inverseMomentOfInertia).produit(rotationMatrix.transposer());

	// Integration des torques sur le moment d'inertie
	auto it1 = tempTorques.begin();
	while (it1 != tempTorques.end()) {
		double applicationTime = (*it1)->updateTimeElapsed(dt);

		// Application du torque pour mettre a jour la vitesse angulaire
		angularVelocity += (*it1)->torque * inverseMomentOfInertia * dt;

		// Suppression de la force rotationnelle si sa duree est terminee
		if (applicationTime >= (*it1)->duration) {
			it1 = tempTorques.erase(it1);
		}
		else {
			++it1;
		}
	}

	// Int�gration de la vitesse angulaire sur la rotation
	rotation = computeNewRotation(rotation, angularVelocity, dt);
	rotation = rotation.normalize();

	// Mise � jour de la matrice de rotation
	rotationMatrix = rotation.getRotationMatrix();

		
}

Quaternion CorpsRigide::computeNewRotation(Quaternion q, Vector w, double dt) {
	Quaternion rotationChange = Quaternion(0, w) * q;
	rotationChange = (rotationChange / 2.0f) * dt;
	return q + rotationChange;
}

void CorpsRigide::setRotation(Quaternion quaternion) {
	this->rotation = quaternion;
}

void CorpsRigide::ofApplyVisualRotation() {
	Vector visualRotation = this->rotationMatrix.getEuler();

	ofRotateZRad(visualRotation.z());
	ofRotateYRad(visualRotation.y());
	ofRotateXRad(visualRotation.x());
}
