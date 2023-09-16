#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>

//--------------------------------------------------------------
void ofApp::setup(){
	// Exemple calcul
	Vector vectA = Vector(1, 5, -2);
	Vector vectB = Vector(4, 3, 9);

	Vector vectSum = vectA + vectB;

	cout << "Vecteur initiaux " << vectA << ", " << vectB << endl;
	cout << "Somme des vecteurs " << vectSum << endl;

	// Initialisation position boîte
	position = Vector(1, 1, 1);
	size = 10.;
	mouvement = Vector(1, 1, 0);

	// Initialisation liste particules
	list<Particle> particles;

	// Initialisation particules
	Particle particle1 = Particle(Vector(1, 1, 1), 1, ofColor(255, 0, 0));
	Particle particle2 = Particle(Vector(1, 1, 1), 1, ofColor(0, 255, 0));
	Particle particle3 = Particle(Vector(1, 1, 1), 1, ofColor(0, 0, 255));

	particle1.applyForce(1, 2, 0);
	particle1.setSize(10);
	particle2.applyForce(0, 1, 0);
	particle2.setSize(10);
	particle3.applyForce(0, 0, 1);
	particle3.setSize(10);

	// Ajout particules à la liste
	particles.push_back(particle1);
	particles.push_back(particle2);
	particles.push_back(particle3);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (position.x() > 1000 || position.x() < 0) {
		mouvement *= -1;
	}
	position += mouvement;

	// Update particules
	for (Particle particle : particles) {
		particle.update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofDrawBox(position.v3(), size);
	ofDrawCircle(position.v3(), size);

	// Draw particules
	for (Particle particle : particles) {
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
