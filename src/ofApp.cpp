#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>

//--------------------------------------------------------------
void ofApp::setup(){
	// Framerate
	ofSetFrameRate(60);


	// Initialisation particules
	particle1.setPos(10, 100, 0);

	particle2.setPos(1, 0, 0);
	particle2.setMass(1);
	particle2.setColor(ofColor(0, 255, 0));

	particle3.setPos(1, 1, 0);
	particle3.setMass(1);
	particle3.setColor(ofColor(0, 0, 255));

	particle1.setSize(10);
	particle2.setSize(10);
	particle3.setSize(10);

	particle1.applyForce(20, 0, 0, 2);
	particle2.applyForce(20, 0, 0, 4);
	particle3.applyForce(20, 0, 0, 6);

	particle2.setRestitution(0.5);
	particle3.setRestitution(0.5);

	particle2.setFriction(0.99);
	particle3.setFriction(0.99);

	// Ajout particules dans la liste
	//particles.push_back(particle1);
	fireballs.push_back(particle1); //on range la boule de feu dans une liste faite pour les boules de feu (update override ne fonctionnant pas)
	particles.push_back(particle2);
	particles.push_back(particle3);
}

//--------------------------------------------------------------
void ofApp::update() {
	// Update particules
	//for (Particle& particle : particles) {
	for (Fireball& particle : fireballs) {
		particle.update();

		if (particle.getPos().x() > 1000 || particle.getPos().x() < 0) {
			float x = particle.getPos().x();
			if (x > 1000) {
				particle.setPos(1000, particle.getPos().y(), particle.getPos().z());
				particle.bounce(Vector(-1, 0, 0));
			}
			else {
				particle.setPos(0, particle.getPos().y(), particle.getPos().z());
				particle.bounce(Vector(1, 0, 0));
			}
		}
		if (particle.getPos().y() > 1000 || particle.getPos().y() < 0) {
			float y = particle.getPos().y();
			if (y > 1000) {
				particle.setPos(particle.getPos().x(), 1000, particle.getPos().z());
				particle.bounce(Vector(0, -1, 0));
			}
			else {
				particle.setPos(particle.getPos().x(), 0, particle.getPos().z());
				particle.bounce(Vector(0, 1, 0));
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw particules
	for (Particle& particle : particles) {
		particle.draw();
	}
	for (Fireball& particle : fireballs) { //liste de boule de feu, le draw override ne fonctionnant pas
		particle.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
