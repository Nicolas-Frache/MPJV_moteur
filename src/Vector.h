#pragma once

#include "ofMain.h"

class Vector
{
	private:
		float _X = 0.0f;
		float _Y = 0.0f;
		float _Z = 0.0f;


	public:

		Vector(float X, float Y, float Z);

		// setters
		void set(float X, float Y, float Z);

		// operators
		Vector operator+(Vector vect);
		void operator+=(Vector vect);
		Vector operator-();
		Vector operator-(Vector vect);
		void operator-=(Vector vect);
		Vector operator*(float mult);
		void operator*=(float mult);
		friend ostream& operator<<(ostream& os, const Vector vect);

		float norm();
		Vector normalize();
		float norm2();

		Vector mult_by_component(Vector vect);
		float scalar_product(Vector vect);
		

		// getters
		float x();
		float y();
		float z();

		glm::vec2 v2() { return glm::vec2(_X, _Y); }
		glm::vec3 v3() { return glm::vec3(_X, _Y, _Z); }

};

