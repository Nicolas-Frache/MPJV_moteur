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
	//cube.applyForce(Vector(0,1,0), 0.1);
	//cube.applyTorque(Vector(0, 100, 100), 1);
	cube.angularVelocity = Vector(0, 1, 1);
	corpsRigides.push_back(&cube);
	world.addCorps(&cube); //je sais pas si la liste corpsRigides est utile puisqu'on utilise world
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
