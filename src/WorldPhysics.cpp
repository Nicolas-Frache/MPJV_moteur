#include "WorldPhysics.h"

WorldPhysics::WorldPhysics()
{
}

WorldPhysics::WorldPhysics(float x_size, float y_size, float z_size)
{
	this->_x_size = x_size;
	this->_y_size = y_size;
	this->_z_size = z_size;
}

void WorldPhysics::update()
{
	updateCollisions();
	updateBoundaries();
	updateRodConstraints();

	// Update particules
	for (Particle* particle : particles) {
		particle->update();
	}
	for (CorpsRigide* corps : corpsRigides) {
		corps->update();
	}
}

void WorldPhysics::addParticle(Particle* particle)
{
	particles.push_back(particle);
}

void WorldPhysics::removeParticle(Particle* particle)
{
	particles.erase(std::remove(particles.begin(), particles.end(), particle), particles.end());
}

void WorldPhysics::addCorps(CorpsRigide* corps)
{
	corpsRigides.push_back(corps);
}

void WorldPhysics::removeCorps(CorpsRigide* corps)
{
	corpsRigides.erase(std::remove(corpsRigides.begin(), corpsRigides.end(), corps), corpsRigides.end());
}

void WorldPhysics::addRodConstraint(Particle* particle1, Particle* particle2, float length)
{
	RodConstraint* rodConstraint = new RodConstraint(particle1, particle2, length);
	rodConstraints.push_back(rodConstraint);
}

void WorldPhysics::removeRodConstraint(Particle* particle1, Particle* particle2)
{
	for (int i = 0; i < rodConstraints.size(); i++) {
		RodConstraint* rodConstraint = rodConstraints[i];
		if (rodConstraint->getParticle1() == particle1 && rodConstraint->getParticle2() == particle2) {
			rodConstraints.erase(rodConstraints.begin() + i);
			return;
		}
	}
}


void WorldPhysics::updateCollisions()
{
	// OcTree
	PhysicsObject::resetId();
	for (Particle* particle : particles) {
		new PhysicsObject(particle);
	}
	for (CorpsRigide* corps : corpsRigides) {
		new PhysicsObject(corps);
	}

	if (PhysicsObject::getLastId() < 1) {
		return;
	}

	vector<set<int>> potentialCollisionList = vector<set<int>>(PhysicsObject::getLastId(), set<int>());

	ocTree = new OcTree(PhysicsObject::getObjectsVector(), 1, 6, &potentialCollisionList);

	ocTree->getPossibleCollisions();


	//int totalCollisions = 0;
	//for (set<int> collisions : potentialCollisionList) {
	//	totalCollisions += collisions.size();
	//}
	//cout << "Total collisions a tester: " << totalCollisions << endl;


	detectCollisions(&potentialCollisionList);
}


void WorldPhysics::detectCollisions(vector<set<int>>* potentialCollisions)
{
	debugCollisions.clear();
	debugCollisionsNormals.clear();
	debugCollisionsPoints.clear();
	debugCollisionsPointsNormals.clear();

	for (int i = 0; i < potentialCollisions->size(); i++) {
		set<int> collisions = (*potentialCollisions)[i];
		for (int j : collisions) {
			PhysicsObject* object1 = PhysicsObject::getObjectById(i);
			PhysicsObject* object2 = PhysicsObject::getObjectById(j);

			if (object1->getType() == 0 && object2->getType() == 0) {
				detectParticleCollisions(object1, *object2);
				continue;
			}

			Collision collision = Collision(object1, object2);

			collision.detect();

			if (collision.collisionData().isColliding()) {
				debugCollisions.push_back(collision.collisionData().point());
				debugCollisionsNormals.push_back(collision.collisionData().normal());

				for (const Vector &v : collision.getDebugCollisions()) {
					debugCollisionsPoints.push_back(v);
				}
				for (const Vector &v : collision.getDebugCollisionsNormals()) {
					debugCollisionsPointsNormals.push_back(v);
				}

				collision.resolve();
			}
		}
	}
}

void WorldPhysics::detectParticleCollisions(PhysicsObject* particle1, PhysicsObject particle2)
{
	// Vérifier si une collision se produit entre les deux particules
	Particle *p1 = particle1->getParticle(), *p2 = particle2.getParticle();
	if (p1->checkCollisionWith(*p2)) {
		p1->resolveInterpenetration(*p2);
		Impulse(p1, p2);
	}
}


void WorldPhysics::updateBoundaries()
{

	for (Particle* particle : particles) {

		particle->update();

		auto pos = particle->_position;
		//cout << "POS: " << pos << endl;

		float x = pos.x(), y = pos.y(), z = pos.z();


		if (x > _x_size || x < -_x_size) {
			if (x > _x_size) {
				particle->setPos(_x_size, y, z);
				particle->bounce(Vector(-1, 0, 0));
			}
			else {
				particle->setPos(-_x_size, y, z);
				particle->bounce(Vector(1, 0, 0));
			}
		}
		if (y > _y_size || y < 0) {
			if (y > _y_size) {
				particle->setPos(x, _y_size, z);
				particle->bounce(Vector(0, -1, 0));
			}
			else {
				particle->setPos(x, 0, z);
				particle->bounce(Vector(0, 1, 0));
			}
		}
		if (z > _z_size || z < -_z_size) {
			if (z > _z_size) {
				particle->setPos(x, y, _z_size);
				particle->bounce(Vector(0, 0, -1));
			}
			else {
				particle->setPos(x, y, -_z_size);
				particle->bounce(Vector(0, 0, 1));
			}
		}
	}

	for (CorpsRigide* corps : corpsRigides) {

		corps->update();

		auto pos = corps->centreMasse->_position;
		//cout << "POS: " << pos << endl;

		float x = pos.x(), y = pos.y(), z = pos.z();


		if (x > _x_size || x < -_x_size) {
			if (x > _x_size) {
				corps->centreMasse->setPos(_x_size, y, z);
				corps->centreMasse->bounce(Vector(-1, 0, 0));
			}
			else {
				corps->centreMasse->setPos(-_x_size, y, z);
				corps->centreMasse->bounce(Vector(1, 0, 0));
			}
		}
		if (y > _y_size || y < 0) {
			if (y > _y_size) {
				corps->centreMasse->setPos(x, _y_size, z);
				corps->centreMasse->bounce(Vector(0, -1, 0));
			}
			else {
				corps->centreMasse->setPos(x, 0, z);
				corps->centreMasse->bounce(Vector(0, 1, 0));
			}
		}
		if (z > _z_size || z < -_z_size) {
			if (z > _z_size) {
				corps->centreMasse->setPos(x, y, _z_size);
				corps->centreMasse->bounce(Vector(0, 0, -1));
			}
			else {
				corps->centreMasse->setPos(x, y, -_z_size);
				corps->centreMasse->bounce(Vector(0, 0, 1));
			}
		}
	}

}


void WorldPhysics::updateRodConstraints()
{
	for (RodConstraint* rodConstraint : rodConstraints) {
		rodConstraint->satisfyConstraint();
	}
}


void WorldPhysics::debugDraw()
{
	ofSetLineWidth(1);
	if (ocTree != nullptr)
		ocTree->draw();

	for (int i = 0; i < debugCollisions.size(); i++) {
		Vector collision = debugCollisions[i];
		Vector normal = debugCollisionsNormals[i];

		ofSetColor(255, 0, 0);
		ofDrawSphere(collision.x(), collision.y(), collision.z(), 0.1);

		ofSetColor(0, 255, 0);
		ofDrawLine(collision.x(), collision.y(), collision.z(), collision.x() + normal.x(), collision.y() + normal.y(), collision.z() + normal.z());
	}

	for (int i = 0; i < debugCollisionsPoints.size(); i++) {
		Vector collision = debugCollisionsPoints[i];
		Vector normal = debugCollisionsPointsNormals[i] / 2;

		ofSetColor(255, 0, 0);
		ofDrawSphere(collision.x(), collision.y(), collision.z(), 0.02);

		ofSetColor(144, 255, 0);
		ofDrawLine(collision.x(), collision.y(), collision.z(), collision.x() + normal.x(), collision.y() + normal.y(), collision.z() + normal.z());
	}
}