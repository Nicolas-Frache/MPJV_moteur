#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>
#include "../Ball.h"

//--------------------------------------------------------------
void ofApp::setup(){
	// Exemple calcul
	Vector vectA = Vector(1, 5, -2);
	Vector vectB = Vector(4, 3, 9);

	Vector vectSum = vectA + vectB;

	cout << "Vecteur initiaux " << vectA << ", " << vectB << endl;
	cout << "Somme des vecteurs " << vectSum << endl;

	// Initialisation position bo�te
	position = Vector(1, 1, 0);
	size = 10.;
	mouvement = Vector(1, 1, 0);

	// Initialisation particules
	particle1.setPos(10, 100, 0);
	particle1.setMass(1);
	particle1.setColor(ofColor_<unsigned short>::yellow);

	particle2.setPos(1, 1, 0);
	particle2.setMass(1);
	particle2.setColor(ofColor(0, 255, 0));

	particle3.setPos(1, 1, 0);
	particle3.setMass(1);
	particle3.setColor(ofColor(0, 0, 255));

	particle1.applyForce(1, 2, 0);
	particle1.setSize(10);
	particle2.applyForce(0, 1, 0);
	particle2.setSize(10);
	particle3.applyForce(1, 1, 0);
	particle3.setSize(10);
	


	// Ajout particules � la liste
	particles.push_back(particle1);
	particles.push_back(particle2);
	particles.push_back(particle3);

	//on affiche la velocit� des particules
}

//--------------------------------------------------------------
void ofApp::update(){
	if (position.x() > 1000 || position.x() < 0) {
		mouvement *= -1;
	}
	position += mouvement;

	// Update particules
	for (Particle& particle : particles) {
		particle.update();

		/*if (particle.getPos().x() > 1000 || particle.getPos().x() < 0) {
			particle.setVelocity(-particle.getVelocity());
		}*/
	}

	// Update Ball
	for (Ball& ball : ball) {
		ball.update();
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofDrawBox(position.v3(), size);
	ofSetColor(255, 255, 255);
	ofDrawCircle(position.v3(), size);

	// Draw particules
	for (Particle& particle : particles) {
		particle.draw();
	}

	// Draw ball
	for (Ball& ball : ball) {
		ball.draw();
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
