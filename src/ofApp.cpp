#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>

//--------------------------------------------------------------
void ofApp::setup(){

	skybox.load();


	// Réglages de la caméra
	ofEnableDepthTest();

	// Framerate
	ofSetFrameRate(144);
	cam.setFarClip(200000);
	
	// Initialisation particules
	particle1.applyForce(5, 1, 0, 2);
	particle2.applyForce(5, 0, 20, 4);
	particle3.applyForce(5, 0, 0, 6);

	particle2.setRestitution(0.5);
	particle3.setRestitution(0.5);

	particle2.setFriction(0.99);
	particle3.setFriction(0.99);

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
		if(particle.getPos().y() > 1000 || particle.getPos().y() <0){
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
	cam.begin();
	skybox.draw();
	ofDrawGrid(20.0f, 50, true);

	// Draw particules
	for (Particle& particle : particles) {
		particle.draw();
	}


	cam.end();


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
