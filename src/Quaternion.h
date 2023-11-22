// quaternion.h

#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>

class Quaternion {
public:
  Quaternion();
  Quaternion(double w, double x, double y, double z);

  void print() const;
  double norm() const;
  Quaternion normalize();
  Quaternion conjugate() const;
  Quaternion inverse() const;
  
  Quaternion operator*(const Quaternion& other) const;
  bool Quaternion::operator==(Quaternion other);
  bool Quaternion::operator!=(Quaternion other);
  Quaternion Quaternion::operator/(double scalar) const;
  Quaternion Quaternion::operator-(Quaternion q2) const;
  double dotProduct(Quaternion q2) const;
  Quaternion power(double scalar) const;
  Quaternion slerp(Quaternion q2, double t) const;


public:
  double w, x, y, z;
};

#endif // QUATERNION_H
