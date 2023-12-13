#pragma once

#include "Particle.h"
#include "CorpsRigide.h"
#include "PhysicsObject.h"
#include "GeometricForms.h"

class CollisionData {
	public:
		CollisionData() :
			_object1(NULL), _object2(NULL), _normal(Vector(NULL, NULL, NULL)), _point(Vector(NULL, NULL, NULL)), _penetration(NULL) {}
		CollisionData(PhysicsObject *object1, PhysicsObject *object2, Vector normal, Vector point, float penetration) :
			_object1(object1), _object2(object2), _normal(normal), _point(point), _penetration(penetration) {}

		PhysicsObject* object1() const { return _object1; }
		PhysicsObject* object2() const { return _object2; }

		Vector normal() const { return _normal; }
		Vector point() const { return _point; }
		double penetration() const { return _penetration; }

	private:
		PhysicsObject* _object1;
		PhysicsObject* _object2;
		Vector _normal;
		Vector _point;
		double _penetration;
};

class Collision
{
	public:
		Collision(PhysicsObject *object1, PhysicsObject *object2);

		CollisionData collisionData() const { return _collisionData; }

		void detect();
		void resolve();

	private:
		PhysicsObject *_object1;
		PhysicsObject *_object2;

		CollisionData _collisionData;

		//void detectFaceToFaceCollisions(Face face1, Face face2);
		//void detectFaceToEdgeCollisions(Face face, Edge edge);
		//void detectEdgeToEdgeCollisions(Edge edge1, Edge edge2);

		CollisionData detectEdgesToFacesCollisions(vector<Edge> edges, vector<Face> faces);

		void detectParticleToParticleCollisions(Particle* particle1, Particle* particle2);
		void resolveParticleToParticleCollisions(Particle* particle1, Particle* particle2, CollisionData collisionData);

		void detectCorpsRigideToCorpsRigideCollisions(CorpsRigide* corpsRigide1, CorpsRigide* corpsRigide2);
		void resolveCorpsRigideToCorpsRigideCollisions(CorpsRigide* corpsRigide1, CorpsRigide* corpsRigide2, CollisionData collisionData);

		void detectParticleToCorpsRigideCollisions(Particle* particle, CorpsRigide* corpsRigide);
		void resolveParticleToCorpsRigideCollisions(Particle* particle, CorpsRigide* corpsRigide, CollisionData collisionData);


};

