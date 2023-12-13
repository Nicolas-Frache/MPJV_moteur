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

	CorpsRigide* cube = new CorpsRigide(new Particle(Vector(-5, 0, 0), 1, ofColor::blue, 1), 5, 5, 5, ofColor::blue);
	cube->centreMasse->velocity = Vector(1, 0, 0);
	//cube->centreMasse->applyForce(new ConstantForce(cube->centreMasse, Vector(0, 9.8, 0)));
	createCorpsRigide(cube);

	CorpsRigide* cube2 = new CorpsRigide(new Particle(Vector(5, 0, -1), 1, ofColor::blue, 1), 5, 3, 2, ofColor::red);
	cube2->centreMasse->velocity = Vector(-1, 0, 0);
	//cube2->setRotation(Quaternion(cos(pi / 4), 0, sin(pi / 4), 0));
	//cube2->centreMasse->applyForce(new ConstantForce(cube2->centreMasse, Vector(0, 9.8, 0)));
	createCorpsRigide(cube2);

	//CorpsRigide* cube0 = new CorpsRigide(new Particle(Vector(-1, 0, 0), 10, ofColor::blue, 1), 1, 1, 1, ofColor::red);
	//createCorpsRigide(cube0);
	//cube0->angularVelocity = Vector(-1, 0, 0);

	//CorpsRigide* cube = new CorpsRigide(new Particle(Vector(0, 0, 0), 10, ofColor::blue, 1), 1, 1, 1, ofColor::blue);
	//createCorpsRigide(cube);
	////cube->applyForceAtPosition(new Force(cube->centreMasse, Vector(0, 0, -1.f), .1f), Vector(0, 10, 0));
	//cube->applyTorque(Vector(-100.f, 0, 0), .1f);

	//CorpsRigide* c = new CorpsRigide(new Particle(Vector(3, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::red);
	//c->angularVelocity = Vector(1, 0, 0);
	//createCorpsRigide(c);

	//c = new CorpsRigide(new Particle(Vector(7, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::yellow);
	//c->angularVelocity = Vector(0, 1, 0);
	//createCorpsRigide(c);

	//c = new CorpsRigide(new Particle(Vector(8, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::green);
	//c->angularVelocity = Vector(0, 0, 1);
	//createCorpsRigide(c);
	//
	//c = new CorpsRigide(new Particle(Vector(12, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::red);
	//c->angularVelocity = Vector(1, 1, 0);
	//createCorpsRigide(c);

	//c = new CorpsRigide(new Particle(Vector(15, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::blue);
	//c->angularVelocity = Vector(0, 1, 1);
	//createCorpsRigide(c);

	//c = new CorpsRigide(new Particle(Vector(18, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::purple);
	//c->angularVelocity = Vector(1, 0, 1);
	//createCorpsRigide(c);

	//c = new CorpsRigide(new Particle(Vector(21, 0, 0), 10, ofColor::red, 10), 1.5, 4.5, 1.5, ofColor::limeGreen);
	//c->angularVelocity = Vector(1, 1, 1);
	//createCorpsRigide(c);

	//refCorps = c;

}

//--------------------------------------------------------------
void ofApp::update() {

	if (!pause)
		world.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	menu.draw();
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
		Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, .3);
		newLaser->applyForce(camDir * 200, 0.5);
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
		createCorpsRigide(c);
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
