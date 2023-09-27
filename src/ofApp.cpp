#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>
#include "../Ball.h"
#include "../Laser.h"
#include "ProjectileMenu.h"


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
	
	// Initialisation particules
	particle1.applyForce(5, 1, 10, 2);
	particle2.applyForce(5, 0, 20, 4);
	particle3.applyForce(5, 0, 0, 6);

	particle2.restitution = 0.5;
	particle3.restitution = 0.5;

	particle2.friction =0.99;
	particle3.friction = 0.99;

	// Ajout particules dans la liste
	particles.push_back(&particle1); //on range la boule de feu dans une liste faite pour les boules de feu (update override ne fonctionnant pas)
	particles.push_back(&particle2);
	particles.push_back(&particle3);
}

//--------------------------------------------------------------
void ofApp::update() {

	// Update particules
	for (Particle* particle : particles) {
		particle->update();

		if (particle->getPos().x() > 500 || particle->getPos().x() < -500) {
			float x = particle->getPos().x();
			if (x > 500) {
				particle->setPos(500, particle->getPos().y(), particle->getPos().z());
				particle->bounce(Vector(-1, 0, 0));
			}
			else {
				particle->setPos(-500, particle->getPos().y(), particle->getPos().z());
				particle->bounce(Vector(1, 0, 0));
			}
		}
		if (particle->getPos().y() > 500 || particle->getPos().y() < -500) {
			float y = particle->getPos().y();
			if (y > 500) {
				particle->setPos(particle->getPos().x(), 500, particle->getPos().z());
				particle->bounce(Vector(0, -1, 0));
			}
			else {
				particle->setPos(particle->getPos().x(), -500, particle->getPos().z());
				particle->bounce(Vector(0, 1, 0));
			}
		}
		if (particle->getPos().z() > 500 || particle->getPos().z() < -500) {
			float z = particle->getPos().z();
			if (z > 500) {
				particle->setPos(particle->getPos().x(), particle->getPos().y(), 500);
				particle->bounce(Vector(0, 0, -1));
			}
			else {
				particle->setPos(particle->getPos().x(), particle->getPos().y(), -500);
				particle->bounce(Vector(0, 0, 1));
			}
		}
	}

	// Update balls
	for (Ball* ball : ballParticles) {
		ball->update();

		if (ball->getPos().x() > 500 || ball->getPos().x() < -500) {
			float x = ball->getPos().x();
			if (x > 500) {
				ball->setPos(500, ball->getPos().y(), ball->getPos().z());
				ball->bounce(Vector(-1, 0, 0));
			}
			else {
				ball->setPos(-500, ball->getPos().y(), ball->getPos().z());
				ball->bounce(Vector(1, 0, 0));
			}
		}
		if (ball->getPos().y() > 500 || ball->getPos().y() < -500) {
			float y = ball->getPos().y();
			if (y > 500) {
				ball->setPos(ball->getPos().x(), 500, ball->getPos().z());
				ball->bounce(Vector(0, -1, 0));
			}
			else {
				ball->setPos(ball->getPos().x(), -500, ball->getPos().z());
				ball->bounce(Vector(0, 1, 0));
			}
		}
		if (ball->getPos().z() > 500 || ball->getPos().z() < -500) {
			float z = ball->getPos().z();
			if (z > 500) {
				ball->setPos(ball->getPos().x(), ball->getPos().y(), 500);
				ball->bounce(Vector(0, 0, -1));
			}
			else {
				ball->setPos(ball->getPos().x(), ball->getPos().y(), -500);
				ball->bounce(Vector(0, 0, 1));
			}
		}
	}

	// Update lasers
	for (Laser* laser : laserParticles) {
		laser->update();

		if (laser->getPos().x() > 500 || laser->getPos().x() < -500) {
			float x = laser->getPos().x();
			if (x > 500) {
				laser->setPos(500, laser->getPos().y(), laser->getPos().z());
				laser->bounce(Vector(-1, 0, 0));
			}
			else {
				laser->setPos(-500, laser->getPos().y(), laser->getPos().z());
				laser->bounce(Vector(1, 0, 0));
			}
		}
		if (laser->getPos().y() > 500 || laser->getPos().y() < -500) {
			float y = laser->getPos().y();
			if (y > 500) {
				laser->setPos(laser->getPos().x(), 500, laser->getPos().z());
				laser->bounce(Vector(0, -1, 0));
			}
			else {
				laser->setPos(laser->getPos().x(), -500, laser->getPos().z());
				laser->bounce(Vector(0, 1, 0));
			}
		}
		if (laser->getPos().z() > 500 || laser->getPos().z() < -500) {
			float z = laser->getPos().z();
			if (z > 500) {
				laser->setPos(laser->getPos().x(), laser->getPos().y(), 500);
				laser->bounce(Vector(0, 0, -1));
			}
			else {
				laser->setPos(laser->getPos().x(), laser->getPos().y(), -500);
				laser->bounce(Vector(0, 0, 1));
			}
		}
	}

}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	skybox.draw();
	ofDrawGrid(20.0f, 50, true);

	menu.draw();

	// Draw fireballs and particules
	for (Particle* particle : particles) {
		particle->draw();
	}

	// Draw balls
	for (Ball* ball : ballParticles) {
		ball->draw();
	}

	// Draw lasers
	for (Laser* laser : laserParticles) {
		laser->draw();
	}

	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		// Créez une nouvelle instance de Ball à la position actuelle de la caméra
		Ball* newBall = new Ball(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, 1);

		// Appliquez une force à la nouvelle balle (si nécessaire)
		newBall->applyForce(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, 2);

		// Ajoutez la nouvelle balle à la liste des particules Ball
		ballParticles.push_back(newBall);
	}

	if (key == '2') {
		// Initialisation particules
		// Créez une nouvelle instance de Ball à la position actuelle de la caméra
		Fireball* newFireball = new Fireball(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, 1);

		newFireball->applyForce(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, 1);

		// Ajout particules dans la liste
		particles.push_back(newFireball); //on range la boule de feu dans une liste faite pour les boules de feu (update override ne fonctionnant pas)
	}

	if (key == '3') {
		// Créez une nouvelle instance de Laser à la position actuelle de la caméra
		Laser* newLaser = new Laser(
			cam.getPosition().x, cam.getPosition().y, cam.getPosition().z,
			cam.getLookAtDir().x, cam.getLookAtDir().y, cam.getLookAtDir().z,
			1
		);

		newLaser->applyForce(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z, 1);

		// Ajoutez la nouvelle instance de Laser à la liste des lasers
		laserParticles.push_back(newLaser);
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
