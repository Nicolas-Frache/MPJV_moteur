#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "Fireball.h"
#include "Ball.h"
#include "Cannonball.h"
#include "Laser.h"
#include "../RodConstraint.h"

#include <list>
// https://github.com/kalwalt/ofxSkyBox
#include "addons/ofxSkyBox/ofxSkyBox.h"
// https://github.com/010pe/ofxFirstPersonCamera
#include "addons/ofxFirstPersonCamera/ofxFirstPersonCamera.h"

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
		Fireball particle1 = Fireball(0, 50, 0, 1);
		Particle particle2 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::green), 10);
		Particle particle3 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::blue), 10);
	
		Ball ball = Ball(100, 600, 0, .01, ofColor::red, 5);
		Laser laser = Laser(Vector(2, 0, 0), Vector(1, 1, 1), .01, ofColor::pink, 2);
		Cannonball cannonball = Cannonball(100, 60, 0, 1, ofColor::black, 20);

		ofxSkyBox skybox;
		ofxFirstPersonCamera cam;
		ofVec3f sphereCenter;
		
private:
	std::vector<RodConstraint> rodConstraints;

};
