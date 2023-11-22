// quaternion.h

#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <Matrice3x3.h>

class Quaternion {
public:
  Quaternion();
  Quaternion(double w, double x, double y, double z);
  Quaternion(double w, Vector v) : w(w), x(v.x()), y(v.y()), z(v.z()) {}

  void print() const;
  double norm() const;
  Quaternion normalize();
  Quaternion conjugate() const;
  Quaternion inverse() const;
  
  Quaternion operator+(const Quaternion& other) const;
  Quaternion operator*(const Quaternion& other) const;
  Quaternion operator*(double scalar) const;
  bool Quaternion::operator==(Quaternion other);
  bool Quaternion::operator!=(Quaternion other);
  Quaternion Quaternion::operator/(double scalar) const;
  Quaternion Quaternion::operator-(Quaternion q2) const;
  double dotProduct(Quaternion q2) const;
  Quaternion power(double scalar) const;
  Quaternion slerp(Quaternion q2, double t) const;
  Matrice3x3 getRotationMatrix() const;


public:
  double w, x, y, z;
};

#endif // QUATERNION_H
