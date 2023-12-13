#pragma once

#include "Vector.h"

class PositionAndPenetration {
	public:
		PositionAndPenetration(Vector position, double penetration) :
			_position(position), _penetration(penetration) {}

		Vector position() { return _position; }
		double penetration() { return _penetration; }

	private:
		Vector _position;
		double _penetration;
};

class Face {
	public:
		Face() :
			_position(Vector(INFINITY, INFINITY, INFINITY)), _normal(Vector(INFINITY, INFINITY, INFINITY)), _height(INFINITY), _length(INFINITY) {}
		Face(Vector position, Vector normal, Vector up, double height, double length) :
			_position(position), _normal(normal), _up(up), _height(height), _length(length) {}

		Vector position() { return _position; }
		Vector normal() { return _normal; }
		Vector up() { return _up; }
		Vector right() { return _normal.vectoriel(_up); }
		double length() { return _length; }
		double height() { return _height; }

	private:
		Vector _position;	// Position du premier point de la face (en bas à gauche), quand la normale est dirigée vers l'extérieur
		Vector _normal;
		Vector _up;			// Vecteur unitaire vertical, perpendiculaire à la face
		double _length;		// Si INFINITY, la longueur est infinie
		double _height;		// Si INFINITY, la largeur est infinie
};	

class Edge {
	public:
		Edge() :
			_position(Vector(INFINITY, INFINITY, INFINITY)), _normal(Vector(INFINITY, INFINITY, INFINITY)), _length(INFINITY) {}
		Edge(Vector position, Vector normal, double length) :
			_position(position), _normal(normal), _length(length) {}

		Vector position() { return _position; }
		Vector normal() { return _normal; }
		double length() { return _length; }

		const bool intersectsPlan(Face face) {
			// On néglige le cas où le segment est inclus dans le plan
			return _normal.scalar_product(face.normal()) != 0;
		}

		const PositionAndPenetration intersection(Face face) {
			// On néglige le cas où le segment est inclus dans le plan
			double t = (face.normal().scalar_product(face.position()) - face.normal().scalar_product(_position)) / face.normal().scalar_product(_normal);
			
			Vector intersection = _position + _normal * t;

			double relativeX = (intersection - face.position()).scalar_product(face.up());
			double relativeY = (intersection - face.position()).scalar_product(face.right());

			if (t < 0 || t > _length) return PositionAndPenetration(Vector(INFINITY, INFINITY, INFINITY), INFINITY);
			if (face.height() != INFINITY && (relativeX < 0 || relativeX > face.height())) return PositionAndPenetration(Vector(INFINITY, INFINITY, INFINITY), INFINITY);
			if (face.length() != INFINITY && (relativeY < 0 || relativeY > face.length())) return PositionAndPenetration(Vector(INFINITY, INFINITY, INFINITY), INFINITY);


			return PositionAndPenetration(intersection, _length - t);
		}

	private:
		Vector _position;	// Position du premier point
		Vector _normal;
		double _length;		// Si nulle, la longueur est infinie
};
