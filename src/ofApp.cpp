#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	menu.setup();
	skybox.load();


	// R�glages de la cam�ra
	ofEnableDepthTest();
    
	// Framerate
	ofSetFrameRate(144);
	cam.setFarClip(200000);
	

	//PARTIE CORPS RIGIDES

	CorpsRigide* c = new CorpsRigide(new Particle(Vector(30, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::red);
	c->angularVelocity = Vector(1, 0, 0);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(60, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::yellow);
	c->angularVelocity = Vector(0, 1, 0);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(90, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::green);
	c->angularVelocity = Vector(0, 0, 1);
	createCorpsRigide(c);
	
	c = new CorpsRigide(new Particle(Vector(120, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::red);
	c->angularVelocity = Vector(1, 1, 0);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(150, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::blue);
	c->angularVelocity = Vector(0, 1, 1);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(180, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::purple);
	c->angularVelocity = Vector(1, 0, 1);
	createCorpsRigide(c);

	c = new CorpsRigide(new Particle(Vector(210, 0, 0), 10, ofColor::red, 10), 15, 45, 15, ofColor::limeGreen);
	c->angularVelocity = Vector(1, 1, 1);
	createCorpsRigide(c);


}

//--------------------------------------------------------------
void ofApp::update() {

	world.update();

	ofDrawBox(10, 10, 10, 2, 4, 2);

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
	for (CorpsRigide* corps : corpsRigides) {
		corps->draw();
	}
	cam.end();
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
		Ball* newBall = new Ball(camPos, 1, ofColor::blue, 20);
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

	if (key == '4') {
		int r = ofRandom(0, 255);
		int g = ofRandom(0, 255);
		int b = ofRandom(0, 255);
		int h = ofRandom(10, 30);
		int w = ofRandom(30, 50);

		CorpsRigide* c = new CorpsRigide(new Ball(camPos, .3, ofColor::red, .1), h, w, h, ofColor(r,g,b));
		c->angularVelocity = Vector(ofRandom(0, 1), ofRandom(0, 1), ofRandom(0, 1));
		c->applyTorque(Vector(0, 0, 1), 2);
		c->applyForce(camDir * 200, 0.5);
		createCorpsRigide(c);
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
