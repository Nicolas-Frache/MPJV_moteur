#pragma once

#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
#include "../Ball.h"
#include "../Laser.h"
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
		
		Vector position = Vector(0, 0, 0);
		float size = 1.;
		Vector mouvement = Vector(0, 0, 0);

		list<Particle> particles = list<Particle>();
		Particle particle1 = Particle(0, 0, 0, 1, ofColor(ofColor_<unsigned char>::maroon));
		Particle particle2 = Particle(0, 0, 0, 1, ofColor(255, 255, 255));
		Particle particle3 = Particle(0, 0, 0, 1, ofColor(255, 255, 255));

		// Ajout d'une instance de Ball
		Ball ball = Ball(100, 100, 0, 1, ofColor::red);

		// Ajout d'une instance de Laser
		Laser laser = Laser(200, 200, 0, 300, 300, 0, 1, ofColor::pink);
	
};
