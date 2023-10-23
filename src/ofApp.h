#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "Fireball.h"
#include "Ball.h"
#include "Cannonball.h"
#include "Laser.h"

#include <list>
// https://github.com/kalwalt/ofxSkyBox
#include "addons/ofxSkyBox/ofxSkyBox.h"
// https://github.com/010pe/ofxFirstPersonCamera
#include "addons/ofxFirstPersonCamera/ofxFirstPersonCamera.h"
#include "PhysicsEngine.cpp"

class ofApp : public ofBaseApp {

public:
    // Methode de configuration (appelee une fois au demarrage)
    void setup();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void update();
		void draw();

		list<Particle*> particles = list<Particle*>();

		ofxSkyBox skybox;
		ofxFirstPersonCamera cam;
		ofVec3f sphereCenter;
		
		Ball* ball = new Ball(Vector(0, 30, 0), 1, ofColor::red, 1);
		PhysicsEngine physicsEngine =  PhysicsEngine(&particles);
		Gravity* gravity = new Gravity();
};
