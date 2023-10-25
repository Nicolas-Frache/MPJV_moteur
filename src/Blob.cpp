#include "Blob.h"
#include <RessortForce.h>
#include <DampingForce.h>
#include <ExploForce.h>

Blob::Blob(Vector position, float invertedMass, ofColor color, float size)
: Ball(position, invertedMass, color, size) {
	restitution = 0.7;
}

void Blob::addNode(Ball* ball){
	ball->applyForce(new RessortForce(ball, this, this->size + ball->size, 20, 500));
	ball->applyForce(new DampingForce(ball, 0.5));

	for (int i = 0; i < this->nodes.size(); i++) {
		ball->applyForce(new RessortForce(ball, this->nodes[i], 1.5 * (nodes[i]->size + ball->size), 4, 500));
		this->nodes[i]->applyForce(new RessortForce(this->nodes[i], ball, 1.5 * (nodes[i]->size + ball->size), 4, 500));
	}
	this->nodes.push_back(ball);
}


void Blob::update(){
	Particle::update();
}

void Blob::splitBlob(){
	int nbToSplit = nodes.size() / 2;
	for (int i = 0; i < nbToSplit; i++) {
		Ball* ball = nodes.back();
		nodes.pop_back();
		ball->applyForce(&ExploForce(ball, this->getPosition(), 200, .1));
	}
}

bool Blob::resolveInterpenetration(Particle& other) {
	//on vérifie si la particule n'est pas déjà dans la liste du blob
	bool temp = Particle::resolveInterpenetration(other);
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i] == &other) {
			return temp;
		}
	}
	if (temp) {
		if (dynamic_cast<Ball*>(&other) != nullptr) {
			addNode(dynamic_cast<Ball*>(&other));
		}
		return temp;
	}
}

void Blob::resolveRestingContactWith(Particle& other) {
	Particle::resolveRestingContactWith(other);
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i] == &other) {
			return;
		}
	}
	if (dynamic_cast<Ball*>(&other) != nullptr) {
		addNode(dynamic_cast<Ball*>(&other));
	}
}
