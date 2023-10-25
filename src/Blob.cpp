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

	/*for (int i = 0; i < this->nodes.size(); i++) {
		ball->applyForce(new RessortForce(ball, this->nodes[i], 1.5 * (nodes[i]->size + ball->size), 4, 500));
		this->nodes[i]->applyForce(new RessortForce(this->nodes[i], ball, 1.5 * (nodes[i]->size + ball->size), 4, 500));
	}*/
	this->nodes.push_back(ball);
}


void Blob::update(){
	Particle::update();
}

void Blob::splitBlob(){
	int nbToSplit = ceil(nodes.size()*1.0 / 2);
	cout << nbToSplit << endl;
	cout << nodes.size() / 2 << endl;
	cout << "size" << nodes.size() << endl;


	for (int i = 0; i < nbToSplit; i++) {
		Ball* ball = nodes.back();
		nodes.pop_back();
		ball->applyForce( new ExploForce(ball, this->getPosition(), 200, 10000));

		// On supprime tous les ressorts de la balle
		auto it = ball->_forces.begin();
		while (it != ball->_forces.end()) {
			// on teste si la force est de type RessortForce
			if (RessortForce* ressort = dynamic_cast<RessortForce*>(*it)){
					it = ball->_forces.erase(it);
			}
			else {
				++it;
			}
		}

		// Supression des forces de ressorts comprenant la balle
		for (int j = 0; j < this->nodes.size(); j++) {
			auto it = nodes[j]->_forces.begin();
			while (it != nodes[j]->_forces.end()) {
				// on teste si la force est de type RessortForce
				if (RessortForce* ressort = dynamic_cast<RessortForce*>(*it)){
					// Et on la supprime si elle agit sur la balle
					if (ressort->particle == ball) {
						it = nodes[j]->_forces.erase(it);
					}
					else {
						++it;
					}
				}
				else {
					++it;
				}
			}
		}

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
