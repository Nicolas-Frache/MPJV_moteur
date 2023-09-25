#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>
#include "Ball.h"
#include "Laser.h"
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
	
	//Initialisation de la balle
	ball._rotationZ = 0.0f;
	ball.applyForce(6, -5, 0, 3);
	particles.push_back(&ball);

	
	cannonball.applyForce(0.01, -0.001, 0, 3);
	particles.push_back(&cannonball);

	particles.push_back(&laser);
	


	// Initialisation particules
	particle1.applyForce(5, 1, 10, 2);
	particle2.applyForce(5, 0, 20, 4);
	particle3.applyForce(5, 0, 0, 6);

	particle2.setRestitution(0.5);
	particle3.setRestitution(0.5);

	particle2.setFriction(0.99);
	particle3.setFriction(0.99);

	// Ajout particules dans la liste
	//particles.push_back(particle1);
	particles.push_back(&particle1); //on range la boule de feu dans une liste faite pour les boules de feu (update override ne fonctionnant pas)
	particles.push_back(&particle2);
	particles.push_back(&particle3);
}

//--------------------------------------------------------------
void ofApp::update() {

	// Update particules
	for (Particle* particle : particles) {
	//for (Fireball& particle : fireballs) {
		particle->update();

		if (particle->getPos().x() > 1000 || particle->getPos().x() < 0) {
			float x = particle->getPos().x();
			if (x > 1000) {
				particle->setPos(1000, particle->getPos().y(), particle->getPos().z());
				particle->bounce(Vector(-1, 0, 0));
			}
			else {
				particle->setPos(0, particle->getPos().y(), particle->getPos().z());
				particle->bounce(Vector(1, 0, 0));
			}
		}
		if (particle->getPos().y() > 1000 || particle->getPos().y() < 0) {
			float y = particle->getPos().y();
			if (y > 1000) {
				particle->setPos(particle->getPos().x(), 1000, particle->getPos().z());
				particle->bounce(Vector(0, -1, 0));
			}
			else {
				particle->setPos(particle->getPos().x(), 0, particle->getPos().z());
				particle->bounce(Vector(0, 1, 0));
			}
		}
	}

	// Update particules
	for (Particle* particle : particles) {
		particle->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	menu.draw();
	cam.begin();
    skybox.draw();
	ofDrawGrid(20.0f, 50, true);

	// Draw particules
	for (Particle* particle : particles) {
		particle->draw();
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

	if (key == '1') {

		// Ajoutez un message pour indiquer que la balle a été créée
		cout << "Balle creee !" << endl;
	}
	else if (key == '2') {


		cout << "Boulet cree !" << endl;
	}
	else if (key == '3') {

		cout << "Laser cree !" << endl;
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
