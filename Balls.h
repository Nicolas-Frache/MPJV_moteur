#pragma once
#include "ofMain.h"
#include "Particle.h"


class Balls extends Particle{

private:
	Vector _position = Vector(0, 0, 0);
	//rotation non utile car particule

	Vector _velocity = Vector(, 0, 0);
	Vector _force = Vector(0, 0, 0);

	float _invertedMass = 1.0f;
	ofColor _color = ofColor(255, 255, 0); //�a parait �tre une bonne id�e de pouvoir choisir la couleur pour faire des tests plus tard
	float _size = 2.0f;

};

