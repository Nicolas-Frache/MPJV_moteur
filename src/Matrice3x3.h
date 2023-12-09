#pragma once

#ifndef matrice3_h
#define matrice3_h

#include "Vector.h"

class Matrice3x3 {
public:
    Matrice3x3();
    Matrice3x3(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22);

    Matrice3x3 produit(const Matrice3x3& other) const;
    Matrice3x3 somme(const Matrice3x3& other) const;
    bool operator==(const Matrice3x3& other) const;
    Matrice3x3 inverse() const;
    Matrice3x3 transposer() const;
    double calculerDeterminant() const;
    bool estOrthonormee() const;
    bool estOrthogonale() const;
    bool estCarree() const;
    double calculerMinor(int i, int j) const;

    Vector getEuler() const;

    void afficher() const;


public:
    double mat[3][3];
};


#endif // !matrice3_h