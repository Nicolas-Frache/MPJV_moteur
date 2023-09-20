#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>

//--------------------------------------------------------------
void ofApp::setup(){
	// Framerate
	ofSetFrameRate(60);


	// Initialisation particules
	particle1.setSize(10);
	particle2.setSize(10);
	particle3.setSize(10);

	particle1.applyForce(20, 0, 0, 2);
	particle2.applyForce(20, 0, 0, 4);
	particle3.applyForce(20, 0, 0, 6);

	// Ajout particules dans la liste
	particles.push_back(particle1);
	particles.push_back(particle2);
	particles.push_back(particle3);
}

//--------------------------------------------------------------
void ofApp::update(){

	// Update particules
	for (Particle& particle : particles) {
		particle.update();

		if (particle.getPos().x() > 1000 || particle.getPos().x() < 0) {
			particle.setVelocity(-particle.getVelocity());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw particules
	for (Particle& particle : particles) {
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
