#pragma once

#ifndef vector_h
#define vector_h

#include "ofMain.h"

class Matrice3x3;

class Vector
{
	private:
		double _X = 0.0f;
		double _Y = 0.0f;
		double _Z = 0.0f;


	public:

		Vector();
		Vector(double X, double Y, double Z);

		// setters
		void set(double X, double Y, double Z);
		void setX(double X) { _X = X;}
		void setY(double Y) { _Y = Y;}
		void setZ(double Z) { _Z = Z;}


		// operators
		Vector operator+(Vector vect);
		void operator+=(Vector vect);
		Vector operator-();
		Vector operator-(Vector vect);
		Vector operator-(const Vector& val) const;
		void operator-=(Vector vect);
		Vector operator*(double mult);
		void operator*=(double mult);
		Vector operator*(const Matrice3x3& mat);
		Vector operator/(double div);
		void operator/=(double div);
		bool operator==(Vector vect);
		friend ostream& operator<<(ostream& os, const Vector vect);

		double norm();
		Vector normalize();
		double norm2();

		Vector mult_by_component(Vector vect);
		Vector vectoriel(Vector vect);

		double scalar_product(Vector vect);
		double distance(const Vector& other) const;
		

		// getters
		double x();
		double y();
		double z();

		glm::vec2 v2() { return glm::vec2(_X, _Y); }
		glm::vec3 v3() { return glm::vec3(_X, _Y, _Z); }

};

#endif // !vector_h