#pragma once

#ifndef vector_h
#define vector_h

#include "ofMain.h"

class Matrice3x3;

class Vector
{
	private:
		float _X = 0.0f;
		float _Y = 0.0f;
		float _Z = 0.0f;


	public:

		Vector();
		Vector(float X, float Y, float Z);

		// setters
		void set(float X, float Y, float Z);
		void setY(float Y);

		// operators
		Vector operator+(Vector vect);
		void operator+=(Vector vect);
		Vector operator-();
		Vector operator-(Vector vect);
		Vector operator-(const Vector& val) const;
		void operator-=(Vector vect);
		Vector operator*(float mult);
		void operator*=(float mult);
		Vector operator*(const Matrice3x3& mat);
		bool operator==(Vector vect);
		friend ostream& operator<<(ostream& os, const Vector vect);

		float norm();
		Vector normalize();
		float norm2();

		Vector mult_by_component(Vector vect);
		Vector vectoriel(Vector vect);

		float scalar_product(Vector vect);
		float distance(const Vector& other) const;
		

		// getters
		float x();
		float y();
		float z();

		glm::vec2 v2() { return glm::vec2(_X, _Y); }
		glm::vec3 v3() { return glm::vec3(_X, _Y, _Z); }

};

#endif // !vector_h