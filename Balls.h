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
	ofColor _color = ofColor(255, 255, 0); //ça parait être une bonne idée de pouvoir choisir la couleur pour faire des tests plus tard
	float _size = 2.0f;

};

