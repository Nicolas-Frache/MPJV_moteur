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

	float x_size = 250;
	float y_size = 500;
	float z_size = 250;

	// Update particules
	for (Particle* particle : particles) {
		particle->update();
		auto pos = particle->position;
		float x = pos.x(), y = pos.y(), z = pos.z();

			
		if (x > x_size || x < -x_size) {
			if (x > x_size) {
				particle->setPos(x_size, y, z);
				particle->bounce(Vector(-1, 0, 0));
			}
			else {
				particle->setPos(-x_size, y, z);
				particle->bounce(Vector(1, 0, 0));
			}
		}
		if (y > y_size || y < 0) {
			if (y > 500) {
				particle->setPos(x, y_size, z);
				particle->bounce(Vector(0, -1, 0));
			}
			else {
				particle->setPos(x, 0, z);
				particle->bounce(Vector(0, 1, 0));
			}
		}
		if (z > z_size || z < -z_size) {
			if (z > z_size) {
				particle->setPos(x, y, z_size);
				particle->bounce(Vector(0, 0, -1));
			}
			else {
				particle->setPos(x, y, -z_size);
				particle->bounce(Vector(0, 0, 1));
			}
		}
	}

	// Update particules
	for (Particle* particle : particles) {
		particle->update();
	}

	ball.setRotationZ(ball.getRotationZ() + 2);
	cannonball.setRotationZ(cannonball.getRotationZ() + 1);
}

//--------------------------------------------------------------
void ofApp::draw(){
	menu.draw();
	cam.begin();
    skybox.draw();
	ofDrawGrid(50, 5, true, true, true, false);

	// Draw particules
	for (Particle* particle : particles) {
		particle->draw();
	}
	cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	Vector camPos;
	Vector camDir;
	if (key == '1' || key == '2' || key == '3') {
		camPos = Vector(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
		auto tmp = cam.getLookAtDir();
		camDir = Vector(tmp.x, tmp.y, tmp.z);
	}


	if (key == '1') {
		Ball* newBall = new Ball(camPos, 1, ofColor::blue, 10);
		newBall->applyForce(camDir * 100, 0.5);
		particles.push_back(newBall);
	}

	if (key == '2') {
		Fireball* newFireball = new Fireball(camPos, 1);
		newFireball->applyForce(camDir * 110, 0.5);
		particles.push_back(newFireball); 
	}

	if (key == '3') {
		Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, 3);
		newLaser->applyForce(camDir * 200, 0.5);
		particles.push_back(newLaser);
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
