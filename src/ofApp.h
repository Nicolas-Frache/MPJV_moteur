#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "Fireball.h"
#include <list>

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


		list<Particle> particles = list<Particle>();
		Particle particle1 = Fireball(0, 0, 0, 1, 5);
		Particle particle2 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::green));
		Particle particle3 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::blue));
};
