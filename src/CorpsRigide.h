#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
class CorpsRigide
{
public:
	Particle* centreMasse;
	Vector demiAxes; //distances du centre de masse aux faces du cube

	ofColor color;

	//il faudra utiliser la physique rotationnelle sur les demi axes
	//pour calculer la rotation du cube
	//Matrix4 rotations; //ou un quaternion? //et genre derrière on l'applique à chaque vertex du cube

	//Elle contiendrait une particule servant de centre de gravité, ainsi que 3 demi axes pointant vers les faces de la boite (conseillé pour cette phase)
	//Ensuite ça permettrait de faire un drawBox() avec ces informations, et d'appliquer les updates etc

	CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color);
	CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color);

	void update();

	void draw();

	void applyForce(Vector force, float duration);

	void integrer(float dt);
};

