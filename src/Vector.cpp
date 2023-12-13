#include "Vector.h"
#include "Matrice3x3.h"
#include <iostream>

Vector::Vector() { //faire un fichier test
	_X = 0;
	_Y = 0;
	_Z = 0;
}

Vector::Vector(double X, double Y, double Z) {
	_X = X;
	_Y = Y;
	_Z = Z;
}

void Vector::set(double X, double Y, double Z) {
	_X = X;
	_Y = Y;
	_Z = Z;
}

// operators
Vector Vector::operator+(Vector vect) {
	double X = _X + vect.x();
	double Y = _Y + vect.y();
	double Z = _Z + vect.z();
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
	double X = _X - vect.x();
	double Y = _Y - vect.y();
	double Z = _Z - vect.z();
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


Vector Vector::operator*(double mult) {
	double X = _X * mult;
	double Y = _Y * mult;
	double Z = _Z * mult;

	return Vector(X, Y, Z);
}


void Vector::operator*=(double mult) {
	_X *= mult;
	_Y *= mult;
	_Z *= mult;
}

Vector Vector::operator*(const Matrice3x3& mat) {
	double X = _X * mat.mat[0][0] + _X * mat.mat[0][1] + _X * mat.mat[0][2];
	double Y = _Y * mat.mat[1][0] + _Y * mat.mat[1][1] + _Y * mat.mat[1][2];
	double Z = _Z * mat.mat[2][0] + _Z * mat.mat[2][1] + _Z * mat.mat[2][2];

	return Vector(X, Y, Z);
}

Vector Vector::operator/(double div)
{
	return Vector(_X / div, _Y / div, _Z / div);
}

void Vector::operator/=(double div) {
	_X /= div;
	_Y /= div;
	_Z /= div;
}

bool Vector::operator==(Vector vect) {
	return _X == vect.x() && _Y == vect.y() && _Z == vect.z();
}

bool Vector::operator!=(Vector vect)
{
	return _X != vect.x() || _Y != vect.y() || _Z != vect.z();
}

ostream& operator<<(ostream& os, Vector vect) {
	os << "(" << vect.x() << "; " << vect.y() << "; " << vect.z() << ")";
	return os;
}

double Vector::norm() {
	return sqrt(_X * _X + _Y * _Y + _Z * _Z);
}

Vector Vector::normalize() {
	double norm = this->norm();
	double X = _X / norm;
	double Y = _Y / norm;
	double Z = _Z / norm;

	return Vector(X, Y, Z);
}

double Vector::norm2() {
	return _X * _X + _Y * _Y + _Z * _Z;
}

Vector Vector::mult_by_component(Vector vect) {
	double X = _X * vect.x();
	double Y = _Y * vect.y();
	double Z = _Z * vect.z();

	return Vector(X, Y, Z);
}

Vector Vector::vectoriel(Vector vect) {
	double X = _Y * vect.z() - _Z * vect.y();
	double Y = _Z * vect.x() - _X * vect.z();
	double Z = _X * vect.y() - _Y * vect.x();
	return Vector(X, Y, Z);
}

double Vector::scalar_product(Vector vect) {
	return _X * vect.x() + _Y * vect.y() + _Z * vect.z();
}


double Vector::distance(const Vector& other) const {
	double dx = _X - other._X;
	double dy = _Y - other._Y;
	double dz = _Z - other._Z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}


double Vector::x() {
	return _X;
}

double Vector::y() {
	return _Y;
}

double Vector::z() {
	return _Z;
}