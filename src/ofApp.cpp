#include "ofApp.h"
#include "Vector.h"

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
}

//--------------------------------------------------------------
void ofApp::update(){
	if (position.x() > 1000 || position.x() < 0) {
		mouvement *= -1;
	}
	position += mouvement;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofDrawBox(position.v3(), size);
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
