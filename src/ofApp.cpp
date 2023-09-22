#include "ofApp.h"
#include "Vector.h"
#include "Particle.h"
#include <list>
#include "../Ball.h"
#include "../Laser.h"

//--------------------------------------------------------------
void ofApp::setup(){

	skybox.load();


	// R�glages de la cam�ra
	ofEnableDepthTest();
    
	// Initialisation position bo�te
	position = Vector(1, 1, 0);
	size = 10.;
	mouvement = Vector(1, 1, 0);

	// Framerate
	ofSetFrameRate(144);
	cam.setFarClip(200000);
	
	//Initialisation de la balle
	ball.setPos(100, 600, 0);
	ball.setMass(0.01);
	ball.setColor(ofColor(255, 0, 0));
	ball.setRotationZ(0.0f);

	ball.applyForce(6, -5, 0);
	ball.setSize(20);

	// Ajout la balle à la liste particules
	particles.push_back(ball);



	//Initialisation du boulet ( le cannonball ) 
	cannonball.setPos(100, 60, 0);
	cannonball.setMass(5);
	cannonball.setColor(ofColor(0, 0, 0));
	cannonball.setRotationZ(0.0f);

	cannonball.applyForce(0.01, -0.001, 0);
	cannonball.setSize(20);

	// Ajout du boulet à la liste particules
	particles.push_back(cannonball);



	//Initialisation du laser
	laser.setStartPoint(Vector(200, 200, 0)); // Position du point de départ
	laser.setEndPoint(Vector(300, 300, 0));   // Position du point final
	laser.setMass(0.01);
	laser.setColor(ofColor(253, 108, 158)); // Couleur du laser, ici rose
	laser.setSize(3);

	laser.applyForce(3, 2, 0); // Appliquer une force au laser

	// Ajout du laser à la liste particules
	particles.push_back(laser);
	


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

	// Update Ball
	for (Ball& ball : ball) {
		ball.update();
		cannonball.update();
		laser.update();

	}

	ball.setRotationZ(ball.getRotationZ() + 2);
	cannonball.setRotationZ(cannonball.getRotationZ() + 1);
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin();
    skybox.draw();
	ofDrawGrid(20.0f, 50, true);

	// Draw particules
	for (Particle* particle : particles) {
		particle->draw();
	}

	// Draw ball
	for (Ball& ball : ball) {
		ball.draw();

		//Draw laser
		laser.draw();

		//Draw le cannonball 
		cannonball.draw();
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
