#include "Vector.h"
#include <iostream>

Vector::Vector() { //faire un fichier test
	_X = 0;
	_Y = 0;
	_Z = 0;
}

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

void Vector::setY(float Y){
	_Y = Y;
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

Vector Vector::operator-(const Vector& val) const {
	return Vector(_X - val._X, _Y - val._Y, _Z - val._Z);
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

bool Vector::operator==(Vector vect) {
	return _X == vect.x() && _Y == vect.y() && _Z == vect.z();
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

Vector Vector::vectoriel(Vector vect) {
	float X = _Y * vect.z() - _Z * vect.y();
	float Y = _Z * vect.x() - _X * vect.z();
	float Z = _X * vect.y() - _Y * vect.x();
	return Vector(X, Y, Z);
}

float Vector::scalar_product(Vector vect) {
	return _X * vect.x() + _Y * vect.y() + _Z * vect.z();
}


float Vector::distance(const Vector& other) const {
	float dx = _X - other._X;
	float dy = _Y - other._Y;
	float dz = _Z - other._Z;
	return sqrt(dx * dx + dy * dy + dz * dz);
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