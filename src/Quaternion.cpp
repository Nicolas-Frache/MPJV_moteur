#include "Quaternion.h"

#include <iostream>
#include <cmath>
#include <Vector.h>

  // Constructeur par défaut, initialise le quaternion à l'élément neutre
  Quaternion::Quaternion() : w(1.0), x(0.0), y(0.0), z(0.0) {}

  // Constructeur avec initialisation explicite
  Quaternion::Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}


  // Méthode pour afficher le quaternion
  void Quaternion::print() const {
    std::cout << "(" << w << ", " << x << ", " << y << ", " << z << ")" << std::endl;
  }

  // Méthode pour calculer la norme du quaternion
  double Quaternion::norm() const {
    return std::sqrt(w * w + x * x + y * y + z * z);
  }

  // Méthode pour normaliser le quaternion
  Quaternion Quaternion::normalize() {
    double n = norm();
    if (n != 0.0) {
      return *this/n;
    }
  }

  // Somme de deux quaternions
  Quaternion Quaternion::operator+(const Quaternion& other) const {
	return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
  }

  // Produit Hamiltonien
  Quaternion Quaternion::operator*(const Quaternion& other) const {
    // Produit Hamiltonien correspondant à la conjugaison de deux roations
    Quaternion result;
    result.x = w * other.x + x * other.w + y * other.z - z * other.y;
    result.y = w * other.y - x * other.z + y * other.w + z * other.x;
    result.z = w * other.z + x * other.y - y * other.x + z * other.w;
    result.w = w * other.w - x * other.x - y * other.y - z * other.z;
    return result;
  }

  // Produit par un scalaire
  Quaternion Quaternion::operator*(double scalar) const {
	return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
  }

  bool Quaternion::operator==(Quaternion q2) {
    return w == q2.w && y == q2.y && w == q2.w && z == q2.z;
  }

  bool Quaternion::operator!=(Quaternion other) {
    return !(other == *this);
  }

  Quaternion Quaternion::operator/(double scalar) const {
    if (scalar != 0.0) {
      return Quaternion(w / scalar, x / scalar, y / scalar, z / scalar);
    }
    else {
      std::cerr << "Error: Division by zero!" << std::endl;
      return Quaternion();
    }
  }

  // Déplacement angulaire entre Q1 et Q2
  Quaternion Quaternion::operator-(Quaternion q2) const{
    // d = Q2 * Q1*
    return *this * q2.conjugate();
  }

  // Produit scalaire (somme des produits terme à terme), la valeur absolu est proportionnelle à la similarité entre les deux quaternions
  double Quaternion::dotProduct(Quaternion q2) const{
    return w*q2.w + x*q2.x + y*q2.y + z*q2.z;
  }

  // Exponentiation : Q^t représente la fraction t du déplacement angulaire Q
  Quaternion Quaternion::power(double t) const{
    double alpha = acos(w);
    Vector v = Vector(x, y, z);
    v = v * (sin(t*alpha)/ sin(alpha));
    return Quaternion(cos(t*alpha), v.x(), v.y(), v.z());
  }

  // Interpolation linéaire entre Q1(this) et Q2 à la fraction t du déplacement angulaire
  Quaternion Quaternion::slerp(Quaternion q2, double t) const{
    return (q2 * this->inverse()).power(t) * (*this);
  }

  // Matrice de rotation associée au quaternion
  Matrice3x3 Quaternion::getRotationMatrix() const{
    Matrice3x3 result;
    result.mat[0][0] = 1 - 2*y*y - 2*z*z;
    result.mat[0][1] = 2*x*y - 2*z*w;
    result.mat[0][2] = 2*x*z + 2*y*w;
    result.mat[1][0] = 2*x*y + 2*z*w;
    result.mat[1][1] = 1 - 2*x*x - 2*z*z;
    result.mat[1][2] = 2*y*z - 2*x*w;
    result.mat[2][0] = 2*x*z - 2*y*w;
    result.mat[2][1] = 2*y*z + 2*x*w;
    result.mat[2][2] = 1 - 2*x*x - 2*y*y;
    return result;
  }

  Quaternion Quaternion::conjugate() const {
    // Q* = w - xi - yj - zk
    return Quaternion(w, -x, -y, -z);
  }

  Quaternion Quaternion::inverse() const{
    // Q^-1 = Q* / ||Q||
    return conjugate() / norm();
  }

