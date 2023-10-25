#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>
#include "Ball.h"
#include "Laser.h"
#include "ProjectileMenu.h"
#include "ConstantForce.h"
#include "CableForce.h"
#include "RessortForce.h"
#include "ElastForce.h"
#include "FrictionStat.h"
#include "ExploForce.h"
#include "WaterForce.h"
#include "../RodConstraint.h"


ProjectileMenu menu;

//--------------------------------------------------------------
void ofApp::setup(){

	menu.setup();
	skybox.load();



	// R�glages de la cam�ra
	ofEnableDepthTest();
    
	// Framerate
	ofSetFrameRate(144);
	cam.setFarClip(200000);
	
	//Initialisation de la balle
	ball._rotationZ = 0.0f;
	ball.applyForce(6, -5, 0, 3);
	particles.push_back(&ball);

	
	cannonball.applyForce(0.01, -0.001, 0, 3);
	particles.push_back(&cannonball);

	particles.push_back(&laser);
	

	// Initialisation particules
	particle1.applyForce(5, 1, 10, 1);
	//particle2.applyForce(5, 0, 20, 4);
	particle3.applyForce(5, 0, 0, 6);

	//tests forces
	//particle1.applyForce(ConstantForce(&particle1, Vector(0, +1, 0), 9.8, 100));
	RessortForce* elast1 = new RessortForce(&particle1, &particle2, 50, 1, 100);
	RessortForce* elast2 = new RessortForce(&particle2, &particle1, 50, 1, 100);
	particle1.applyForce(elast1);
	particle2.applyForce(elast2);
	//fin tests forces


	particle2.restitution = 0.5;
	particle3.restitution = 0.5;

	particle2.friction =0.99;
	particle3.friction = 0.99;

	// Exemple de contrainte de tige
	RodConstraint rod1(&particle1, &particle2, 0);
	RodConstraint rod2(&particle2, &particle3, 30);
	// Ajoutez ces contraintes à une liste de contraintes
	std::vector<RodConstraint> rodConstraints;
	rodConstraints.push_back(rod1);
	rodConstraints.push_back(rod2);

	// Ajout particules dans la liste
	particles.push_back(&particle1); //on range la boule de feu dans une liste faite pour les boules de feu (update override ne fonctionnant pas)
	particles.push_back(&particle2);
	particles.push_back(&particle3);


}

//--------------------------------------------------------------
void ofApp::update() {
	float x_size = 250;
	float y_size = 500;
	float z_size = 250;

	// Mise à jour des particules et gestion des collisions avec les bords
	for (Particle* particle : particles) {
		// Mise à jour de la particule
		particle->update();

		// Gestion des collisions avec les bords de l'environnement
		auto pos = particle->position;
		float x = pos.x(), y = pos.y(), z = pos.z();

		if (x > x_size) {
			particle->setPos(x_size, y, z);
			particle->bounce(Vector(-1, 0, 0));
		}
		else if (x < -x_size) {
			particle->setPos(-x_size, y, z);
			particle->bounce(Vector(1, 0, 0));
		}

		if (y > y_size) {
			particle->setPos(x, y_size, z);
			particle->bounce(Vector(0, -1, 0));
		}
		else if (y < 0) {
			particle->setPos(x, 0, z);
			particle->bounce(Vector(0, 1, 0));
		}

		if (z > z_size) {
			particle->setPos(x, y, z_size);
			particle->bounce(Vector(0, 0, -1));
		}
		else if (z < -z_size) {
			particle->setPos(x, y, -z_size);
			particle->bounce(Vector(0, 0, 1));
		}
	}

	// Gestion des collisions entre les particules
	for (Particle* particleA : particles) {
		for (Particle* particleB : particles) {
			if (particleA != particleB) {
				// Vérifier si une collision se produit entre les deux particules
				if (particleA->checkCollisionWith(*particleB)) {
					// Résoudre la collision entre les deux particules
					particleA->resolveInterpenetration(*particleB);
				}
				// Vérifiez s'il y a une collision douce
				if (particleA->checkRestingContactWith(*particleB)) {
					// Traite la collision au repos ici
					particleA->resolveRestingContactWith(*particleB);
				}
			}
		}
	}

	// Mettez à jour les contraintes de tige
	for (RodConstraint& constraint : rodConstraints) {
		constraint.satisfyConstraint();
	}

	// Détection de collision de type "câble"
	float cableMaxLength = 100.0; // Longueur maximale du câble
	float cableRestitution = 0.9; // Coefficient de restitution pour le câble

	for (Particle* particleA : particles) {
		for (Particle* particleB : particles) {
			if (particleA != particleB) {
				float distance = particleA->getPosition().distance(particleB->getPosition());
				if (distance > cableMaxLength) {
					// Collision de type "câble" détectée
					// Calculez la force de rappel
					Vector direction = particleB->getPosition() - particleA->getPosition();
					direction.normalize();
					float overlap = distance - cableMaxLength;
					Vector force = direction * overlap * cableRestitution;
					// Appliquez la force de rappel aux particules
					particleA->applyForce(force);
					particleB->applyForce(-force);
				}
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {
	menu.draw();
	cam.begin();
	skybox.draw();
	ofDrawGrid(50, 5, true, true, true, false);

	// Dessiner les particules et les contraintes de tige
	for (Particle* particle : particles) {
		particle->draw();
	}

	// Dessiner les contraintes de tige
	for (const RodConstraint& constraint : rodConstraints) {
		Particle* p1 = constraint.getParticle1();
		Particle* p2 = constraint.getParticle2();
		ofSetColor(0, 0, 0);
		ofSetLineWidth(20); // Épaisseur de la ligne pour représenter la contrainte de tige
		ofDrawLine(p1->getPosition().x(), p1->getPosition().y(), p1->getPosition().z(),
			p2->getPosition().x(), p2->getPosition().y(), p2->getPosition().z());
		ofSetLineWidth(1); // Rétablissez l'épaisseur de la ligne par défaut
	}
	float cableMaxLength = 100.0;
	// Dessiner visuellement la collision de type "câble" (ajout)
	ofSetColor(255, 0, 0); // Couleur rouge pour le câble (à ajuster)
	for (Particle* particleA : particles) {
		for (Particle* particleB : particles) {
			if (particleA != particleB) {
				float distance = particleA->getPosition().distance(particleB->getPosition());
				if (distance > cableMaxLength) {
					// Dessinez le câble entre les particules
					ofDrawLine(particleA->getPosition().x(), particleA->getPosition().y(), particleA->getPosition().z(), particleB->getPosition().x(), particleB->getPosition().y(), particleB->getPosition().z());
				}
			}
		}
	}

	cam.end();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	Vector camPos;
	Vector camDir;
	if (key == '1' || key == '2' || key == '3') {
		camPos = Vector(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
		auto tmp = cam.getLookAtDir();
		camDir = Vector(tmp.x, tmp.y, tmp.z);
	}


	if (key == '1') {
		Ball* newBall = new Ball(camPos, 1, ofColor::blue, 10);
		newBall->applyForce(camDir * 100, 0.5);
		particles.push_back(newBall);
	}

	if (key == '2') {
		Fireball* newFireball = new Fireball(camPos, 1);
		newFireball->applyForce(camDir * 110, 0.5);
		particles.push_back(newFireball); 
	}

	if (key == '3') {
		Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, 3);
		newLaser->applyForce(camDir * 200, 0.5);
		particles.push_back(newLaser);
	}

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// Contrôles de la caméra lors du clic droit
	cam.toggleControl();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
