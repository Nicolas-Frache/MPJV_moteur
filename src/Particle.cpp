#include "Particle.h"
#include <limits>

Particle::Particle(Vector position, float invertedMass, ofColor color, float size) {
	this->position = position;
	this->invertedMass = invertedMass;
	this->color = color;
	this->size = size;

	this->sphere = ofSpherePrimitive(10, 10);
	this->sphere.setRadius(size);

	//applyForce(ConstantForce(this, Vector(0, +1, 0), 9.8, 100));
}




void Particle::draw() {
	ofEnableDepthTest();
	ofSetColor(color);
	sphere.setPosition(position.x(), position.y(), position.z());
	sphere.draw();
}


void Particle::update() {

}


void Particle::bounce(Vector normal) {
	velocity = velocity - (normal * ((1+restitution) * velocity.scalar_product(normal)));
	Vector tangent = velocity - (normal * velocity.scalar_product(normal));
	velocity = tangent * friction + normal * velocity.scalar_product(normal);
}

void Particle::integrer(float dt) {
	//std::vector<Force*>::iterator  it = _forces.begin();
	//while (it != _forces.end()) {

	//	//avec force.value on peut utiliser la force pour récup l'accel (Sum(F) = m*a, d'où a = F/m d'où v = F/m * dt)

	//	if (applicationTime != dt) {
	//		it = _forces.erase(it); // Suppression de la force si sa duree est terminee
	//	}
	//	else {
	//		++it; // Element suivant
	//	}
	//}

}
