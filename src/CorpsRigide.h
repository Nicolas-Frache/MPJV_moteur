#pragma once
#include "ofMain.h"
#include "Vector.h"
#include "Particle.h"
//#include "Quaternion.h"
#include "Matrice4x4.h"
#include "ForceRotationnelle.h"
class CorpsRigide
{
public:
	Particle* centreMasse;
	Vector demiAxes; //distances du centre de masse aux faces du cube

	ofColor color;

	Matrice4x4 rotationMatrix = Matrice4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1); //matrice identit�
	Vector angularVelocity = Vector(0, 0, 0);

	Vector inverseMomentOfInertia = Vector(0,0,0);

	list<ForceRotationnelle*> _torques = list<ForceRotationnelle*>();

	//il faudra utiliser la physique rotationnelle sur les demi axes
	//pour calculer la rotation du cube
	//Matrix4 rotations; //ou un quaternion? //et genre derri�re on l'applique � chaque vertex du cube

	CorpsRigide(Particle* centreMasse, Vector demiAxes, ofColor color);
	CorpsRigide(Particle* centreMasse, float height, float width, float depth, ofColor color);

	void update();

	void draw();

	void bounce(Vector normal); //pour le bounce on utilise la resti et friction de la particule

	void applyForce(Vector force, float duration);
	void applyForce(float forceX, float forceY, float forceZ, float duration);
	void applyForce(Force* force);

	void applyTorque(Vector torque, float duration);
	void applyTorque(float torqueX, float torqueY, float torqueZ, float duration);
	void removeTorque(ForceRotationnelle* torque);

	void applyRotation(Vector rotationChange);

	void integrer(float dt);

	void setRotationMatrix(Matrice4x4 matrix);
	//void setRotationMatrix(Quaternion quaternion);

	void ofApplyRotation();
};

