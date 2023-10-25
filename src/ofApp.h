#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "Fireball.h"
#include "Ball.h"
#include "Cannonball.h"
#include "Laser.h"
#include "ConstantForce.h"
#include "CableForce.h"
#include "RessortForce.h"
#include "ElastForce.h"
#include "FrictionStat.h"
#include "ExploForce.h"
#include "WaterForce.h"
#include "DampingForce.h"

#include <list>
// https://github.com/kalwalt/ofxSkyBox
#include "addons/ofxSkyBox/ofxSkyBox.h"
// https://github.com/010pe/ofxFirstPersonCamera
#include "addons/ofxFirstPersonCamera/ofxFirstPersonCamera.h"
#include <Blob.h>

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
		Ball particle1 = Ball(0, 50, 0, 1, ofColor_<unsigned char>::red, 20);
		Ball particle2 = Ball(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::green), 10);
		Ball particle3 = Ball(100, 100, 0, 1, ofColor(ofColor_<unsigned char>::pink), 10);
		Particle* moveable_Particle = &particle1;
	
		Ball ball = Ball(100, 600, 0, .01, ofColor::red, 5);
		Laser laser = Laser(Vector(2, 0, 0), Vector(1, 1, 1), .01, ofColor::pink, 2);
		Cannonball cannonball = Cannonball(0, 0, 0, 1, ofColor::black, 20);
		
		Blob blob = Blob(Vector(50, 20, 0), 1, ofColor::aquamarine, 25);

		ofxSkyBox skybox;
		ofxFirstPersonCamera cam;
		ofVec3f sphereCenter;
		

};
