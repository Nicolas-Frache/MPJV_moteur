#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "Fireball.h"
#include <list>
// https://github.com/kalwalt/ofxSkyBox
#include "addons/ofxSkyBox/ofxSkyBox.h"
// https://github.com/010pe/ofxFirstPersonCamera
#include "addons/ofxFirstPersonCamera/ofxFirstPersonCamera.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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


		list<Particle*> particles = list<Particle*>();
		list<Fireball> fireballs = list<Fireball>();
		Fireball particle1 = Fireball(0, 0, 0, 1);
		Particle particle2 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::green), 10);
		Particle particle3 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::blue), 10);

		ofxSkyBox skybox;
		ofxFirstPersonCamera cam;
		ofVec3f sphereCenter;
		
        Ball ball = Ball(0, 0, 0, 1, ofColor(255, 255, 255));
};
