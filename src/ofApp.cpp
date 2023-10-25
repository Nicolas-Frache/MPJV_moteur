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
	//particles.push_back(&ball);

	
	cannonball.applyForce(0.01, -0.001, 0, 3);
	//particles.push_back(&cannonball);

	//particles.push_back(&laser);
	

	// Initialisation particules
	particle1.applyForce(5, 1, 10, 1);
	//particle2.applyForce(5, 0, 20, 4);
	particle3.applyForce(0, 20, 0, 6);

	//tests forces
	//particle1.applyForce(ConstantForce(&particle1, Vector(0, +1, 0), 9.8, 100));
	RessortForce* elast1 = new RessortForce(&particle1, &particle2, 50, 1, 100);
	RessortForce* elast2 = new RessortForce(&particle2, &particle1, 50, 1, 100);
	particle1.applyForce(elast1);
	particle2.applyForce(elast2);
	//fin tests forces


	particle2.restitution = 0.5;
	particle3.restitution = 0.5;

	particle2.friction =0.99;
	particle3.friction = 0.99;

	//PARTIE BLOB
	//Particle* blob = new Particle(Vector(0, 0, 0), 1, ofColor::yellow, 10);
	moveable_Particle = &blob;
	DampingForce* damp = new DampingForce(&blob, 0.8);
	blob.applyForce(damp);

	blob.addNode(new Ball(100, 0, 30, .5, ofColor::blue, 20));
	blob.addNode(new Ball(150, 0, -30, .5, ofColor::white, 20));
	blob.addNode(new Ball(120, 0, 40, .5, ofColor::red, 20));
	blob.applyForce(20, 10, 20, 1);
	createParticle(&blob);
	createParticle(blob.nodes[0]);
	createParticle(blob.nodes[1]);
	createParticle(blob.nodes[2]);
	
	
	// Ajout particules dans la liste
	//particles.push_back(&particle1);
	//particles.push_back(&particle2);
	//particles.push_back(&particle3);
}

//--------------------------------------------------------------
void ofApp::update() {

	world.update();

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

void ofApp::createParticle(Particle* particle) {
	particles.push_back(particle);
	world.addParticle(particle);
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
		newBall->restitution = 0.5;
		newBall->applyForce(camDir * 100, 0.5);
		createParticle(newBall);
	}

	if (key == '2') {
		Fireball* newFireball = new Fireball(camPos, 1);
		newFireball->restitution = 0.8;
		newFireball->applyForce(camDir * 110, 0.5);
		createParticle(newFireball);
	}

	if (key == '3') {
		Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, 3);
		newLaser->applyForce(camDir * 200, 0.5);
		createParticle(newLaser);
	}

	float speed = 100;

	if (key == OF_KEY_UP) { //on applique une force vers le haut de durée courte
		moveable_Particle->applyForce(0, 0, speed, 0.1);
	}
	if (key == OF_KEY_DOWN) {
		moveable_Particle->applyForce(0, 0, -speed, 0.1);
	}
	if (key == OF_KEY_LEFT) {
		moveable_Particle->applyForce(speed, 0, 0, 0.1);
	}
	if (key == OF_KEY_RIGHT) {
		moveable_Particle->applyForce(-speed, 0, 0, 0.1);
	}
	if (key == 32) { //on applique une force pour sauter de durée courte
		moveable_Particle->applyForce(0, 100, 0, 0.1);
	}
	if (key == OF_KEY_RETURN) {
		blob.splitBlob();
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
