#pragma once

class Matrice3x3 {
public:
    Matrice3x3();
    Matrice3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22);

    Matrice3x3 produit(const Matrice3x3& other) const;
    Matrice3x3 somme(const Matrice3x3& other) const;
    bool operator==(const Matrice3x3& other) const;
    Matrice3x3 inverse() const;
    Matrice3x3 transposer() const;
    float calculerDeterminant() const;
    bool estOrthonormee() const;
    bool estOrthogonale() const;
    bool estCarree() const;

    void afficher() const;


private:
    float mat[3][3];
    float calculerMinor(int i, int j) const;
};