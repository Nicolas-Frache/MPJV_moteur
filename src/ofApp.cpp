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
	particles.push_back(ball);
	Gravity gravity = Gravity();
	physicsEngine.forceRegistry.add(ball, &gravity);
}

//--------------------------------------------------------------
void ofApp::update() {



	float x_size = 250;
	float y_size = 500;
	float z_size = 250;

	physicsEngine.update();

	//for (Particle* particle : particles) {
	//	particle->update();
	//	auto pos = particle->position;
	//	float x = pos.x(), y = pos.y(), z = pos.z();


	//	if (x > x_size || x < -x_size) {
	//		if (x > x_size) {
	//			particle->setPos(x_size, y, z);
	//			particle->bounce(Vector(-1, 0, 0));
	//		}
	//		else {
	//			particle->setPos(-x_size, y, z);
	//			particle->bounce(Vector(1, 0, 0));
	//		}
	//	}
	//	if (y > y_size || y < 0) {
	//		if (y > 500) {
	//			particle->setPos(x, y_size, z);
	//			particle->bounce(Vector(0, -1, 0));
	//		}
	//		else {
	//			particle->setPos(x, 0, z);
	//			particle->bounce(Vector(0, 1, 0));
	//		}
	//	}
	//	if (z > z_size || z < -z_size) {
	//		if (z > z_size) {
	//			particle->setPos(x, y, z_size);
	//			particle->bounce(Vector(0, 0, -1));
	//		}
	//		else {
	//			particle->setPos(x, y, -z_size);
	//			particle->bounce(Vector(0, 0, 1));
	//		}
	//	}
	//}

	//// Update particules
	//for (Particle* particle : particles) {
	//	particle->update();
	//}
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
	//if (key == '1' || key == '2' || key == '3') {
	//	camPos = Vector(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
	//	auto tmp = cam.getLookAtDir();
	//	camDir = Vector(tmp.x, tmp.y, tmp.z);
	//}


	//if (key == '1') {
	//	Ball* newBall = new Ball(camPos, 1, ofColor::blue, 10);
	//	//newBall->applyForce(Force(newBall, camDir * 100, 0.5));
	//	particles.push_back(newBall);
	//}

	//if (key == '2') {
	//	Fireball* newFireball = new Fireball(camPos, 1);
	//	newFireball->applyForce(Force(newFireball, camDir * 110, 0.5));
	//	particles.push_back(newFireball); 
	//}

	//if (key == '3') {
	//	Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, 3);
	//	newLaser->applyForce(Force(newLaser, camDir * 200, 0.5));
	//	particles.push_back(newLaser);
	//}
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
