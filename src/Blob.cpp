#include "Blob.h"
#include <RessortForce.h>
#include <DampingForce.h>

Blob::Blob(Vector position, float invertedMass, ofColor color, float size)
: Ball(position, invertedMass, color, size) {
	
}

void Blob::addNode(Ball* ball){
	ball->applyForce(new RessortForce(ball, this, this->size + ball->size, 20, 500));
	ball->applyForce(new DampingForce(ball, 0.5));
	//this->applyForce(new RessortForce(this, ball, 100, 1, 100));

	for (int i = 0; i < this->nodes.size(); i++) {
		ball->applyForce(new RessortForce(ball, this->nodes[i], 1.5 * (nodes[i]->size + ball->size), .4, 500));
		this->nodes[i]->applyForce(new RessortForce(this->nodes[i], ball, 1.5 * (nodes[i]->size + ball->size), .4, 500));
	}
	this->nodes.push_back(ball);
}


void Blob::update(){
	Particle::update();
	for (int i = 0; i < this->nodes.size(); i++){
		//this->nodes[i]->update();
		//this->nodes[i]->position.setY(0);
		//this->nodes[i]->velocity.setY(0);
		cout << "NODE      " << this->nodes[i]->getVelocity() << endl;
	}
	cout << "BLOB   " << this->getVelocity() << endl;
}
