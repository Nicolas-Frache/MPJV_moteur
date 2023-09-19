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

	// Initialisation particules
	particle1.setPos(10, 100, 0);
	particle1.setMass(1);
	particle1.setColor(ofColor(255, 255, 255));

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

	// Ajout particules à la liste
	particles.push_back(particle1);
	particles.push_back(particle2);
	particles.push_back(particle3);

	//on affiche la velocité des particules
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

		/*if (particle.getPos().x() > 1000 || particle.getPos().x() < 0) {
			particle.setVelocity(-particle.getVelocity());
		}*/
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//ofDrawBox(position.v3(), size);
	ofSetColor(255, 255, 255);
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
