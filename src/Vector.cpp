#include "Vector.h"
#include <iostream>

Vector::Vector(float X, float Y, float Z) {
	_X = X;
	_Y = Y;
	_Z = Z;
}

void Vector::set(float X, float Y, float Z) {
	_X = X;
	_Y = Y;
	_Z = Z;
}


// operators
Vector Vector::operator+(Vector vect) {
	float X = _X + vect.x();
	float Y = _Y + vect.y();
	float Z = _Z + vect.z();
	return Vector(X, Y, Z);
}

void Vector::operator+=(Vector vect) {
	_X += vect.x();
	_Y += vect.y();
	_Z += vect.z();
}

Vector Vector::operator-() {
	return Vector(-_X, -_Y, -_Z);
}

Vector Vector::operator-(Vector vect)
{
	float X = _X - vect.x();
	float Y = _Y - vect.y();
	float Z = _Z - vect.z();
	return Vector(X, Y, Z);
}

void Vector::operator-=(Vector vect) {
	_X -= vect.x();
	_Y -= vect.y();
	_Z -= vect.z();
}


Vector Vector::operator*(float mult) {
	float X = _X * mult;
	float Y = _Y * mult;
	float Z = _Z * mult;

	return Vector(X, Y, Z);
}


void Vector::operator*=(float mult) {
	_X *= mult;
	_Y *= mult;
	_Z *= mult;
}

ostream& operator<<(ostream& os, Vector vect) {
	os << "(" << vect.x() << "; " << vect.y() << "; " << vect.z() << ")";
	return os;
}

float Vector::norm() {
	return sqrt(_X * _X + _Y * _Y + _Z * _Z);
}

Vector Vector::normalize() {
	float norm = this->norm();
	float X = _X / norm;
	float Y = _Y / norm;
	float Z = _Z / norm;

	return Vector(X, Y, Z);
}

float Vector::norm2() {
	return _X * _X + _Y * _Y + _Z * _Z;
}

Vector Vector::mult_by_component(Vector vect) {
	float X = _X * vect.x();
	float Y = _Y * vect.y();
	float Z = _Z * vect.z();

	return Vector(X, Y, Z);
}


float Vector::x() {
	return _X;
}

float Vector::y() {
	return _Y;
}

float Vector::z() {
	return _Z;
}