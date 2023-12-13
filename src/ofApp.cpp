#pragma once
#include "ofApp.h"


CorpsRigide* refCorps;

//--------------------------------------------------------------
void ofApp::setup(){

	menu.setup();
	skybox.load();


	// R�glages de la cam�ra
	ofEnableDepthTest();
    
	// Framerate
	ofSetFrameRate(144);

	// Camera settings
	cam.movespeed = .2f;
	cam.setFarClip(200000);
	cam.setNearClip(0.1);
	

	//PARTIE CORPS RIGIDES

	double pi = 2 * acos(0.0);

	CorpsRigide* cube0 = new CorpsRigide(new Particle(Vector(-1, 0, 0), 10, ofColor::blue, 1), 1, 1, 1, ofColor::red);
	createCorpsRigide(cube0);
	cube0->angularVelocity = Vector(-1, 0, 0);

	CorpsRigide* cube = new CorpsRigide(new Particle(Vector(0, 0, 0), 10, ofColor::blue, 1), 1, 1, 1, ofColor::blue);
	createCorpsRigide(cube);
	cube->applyTorque(Vector(-100.f, 0, 0), .1f);

	CorpsRigide* c = new CorpsRigide(new Particle(Vector(3, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::red);
	c->angularVelocity = Vector(1, 0, 0);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(7, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::yellow);
	c->angularVelocity = Vector(0, 1, 0);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(8, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::green);
	c->angularVelocity = Vector(0, 0, 1);
	createCorpsRigide(c);
	
	c = new CorpsRigide(new Particle(Vector(12, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::red);
	c->angularVelocity = Vector(1, 1, 0);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(15, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::blue);
	c->angularVelocity = Vector(0, 1, 1);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(18, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::purple);
	c->angularVelocity = Vector(1, 0, 1);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(21, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::limeGreen);
	c->angularVelocity = Vector(1, 1, 1);
	createCorpsRigide(c);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (!pause){
		world.update();
	}
	if (inShootGame) {
		shooterUpdate();
  }
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.begin(); 
    skybox.draw();

	if (repere)
		ofDrawGrid(5, 5, true, true, true, false);

	// Draw particules
	for (Particle* particle : particles) {
		particle->draw();
	}
	for (CorpsRigide* corps : corpsRigides) {
		corps->draw();
	}

	// Debug
	if (debug) {
		world.debugDraw();
	}

	cam.end();
	menu.draw();

	if(inShootGame){
		// construction du charù avec le score :
		char scoreString[20];
		sprintf(scoreString, "Score : %d", score);
		menu.drawButton(ofGetWindowWidth()-150, 10, 100, 30,  scoreString);
		ofSetColor(ofColor::green);
		ofSetLineWidth(2);
		float x0 = ofGetWindowWidth() / 2;
		float y0 = ofGetWindowHeight() / 2;
		ofDrawLine(x0, y0-6, x0, y0+6);
		ofDrawLine(x0-6, y0, x0+6, y0);
		ofSetColor(0);
	}
}



void ofApp::createParticle(Particle* particle) {
	particles.push_back(particle);
	world.addParticle(particle);
}

void ofApp::createCorpsRigide(CorpsRigide* corpsRigide) {
	corpsRigides.push_back(corpsRigide);
	world.addCorps(corpsRigide);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	Vector camPos;
	Vector camDir;
	if (key == '1' || key == '2' || key == '3' || key == '4') {
		camPos = Vector(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
		auto tmp = cam.getLookAtDir();
		camDir = Vector(tmp.x, tmp.y, tmp.z);
	}


	if (key == '1') {
		Ball* newBall = new Ball(camPos, 1, ofColor::blue, 2);
		newBall->restitution = 0.5;
		newBall->applyForce(camDir * 40, 0.5);
		createParticle(newBall);
	}

	if (key == '2') {
		Fireball* newFireball = new Fireball(camPos, 1);
		newFireball->restitution = 0.8;
		newFireball->applyForce(camDir * 40, 0.5);
		createParticle(newFireball);
	}

	if (key == '3') {
		Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, .3);
		newLaser->applyForce(camDir * 60, 0.5);
		createParticle(newLaser);
	}

	if (key == '4') {
		int r = ofRandom(0, 255);
		int g = ofRandom(0, 255);
		int b = ofRandom(0, 255);
		int h = ofRandom(1, 3);
		int w = ofRandom(3, 5);

		CorpsRigide* c = new CorpsRigide(new Ball(camPos, 1, ofColor::red, .1), h, w, h, ofColor(r,g,b));
		c->applyForceAtPosition(camDir * 50, camPos, .1);

		float f = 1;
		Vector randomForce = Vector(ofRandom(-f, f), ofRandom(-f, f), ofRandom(-f, f));

		// Applique la force aléatoire à une position aléatoire sur le corps rigide
		Vector randomPosition = Vector(ofRandom(-w / 2, w / 2), ofRandom(-h / 2, h / 2), ofRandom(-h / 2, h / 2));
		c->applyForceAtPosition(randomForce, randomPosition, .1);

		createCorpsRigide(c);
	}

	// INIT GAME
	if (key == '5') {
		particles.clear();
		world.clearAll();
		corpsRigides.clear();

		inShootGame = !inShootGame;
		menu.setShowMenu(false);
		score = 0;
	}

	float speed = 10;

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

	if (key == '!') {
		debug = !debug;
	}
	if (key == 'p') {
		pause = !pause;
	}
	if (key == 'r') {
		repere = !repere;
	}
	if (key == 'm') {
		menu.setShowMenu(!menu.showMenu);
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
		if(button == 2)
				cam.toggleControl();
		if(button == 0 && inShootGame){
				Vector camPos = Vector(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
				auto tmp = cam.getLookAtDir();
				Vector camDir = Vector(tmp.x, tmp.y, tmp.z);

				Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, .3);
				newLaser->applyForce(camDir * 1000, 0.1);
				createParticle(newLaser);
		}
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

void ofApp::shooterUpdate() {
	cam.setPosition(-23, 5, 0);
	time += ofGetLastFrameTime();
	if(messager.consumeCollisionMessage()){
    score++;
		time = 2.7;
  }

	if (time > 3.5) {
		time = 0;

		Ball* newBall = new Ball(Vector(20, 0, -20), 1, ofColor::blue, ofRandom(1, 3));
		newBall->restitution = 0.5;
		newBall->applyForce(Vector(0, ofRandom(20, 50), ofRandom(5,30)), 0.5);
		createParticle(newBall);
	} else if (time > 3){
		particles.clear();
		world.clearAll();
		corpsRigides.clear();
	}
}