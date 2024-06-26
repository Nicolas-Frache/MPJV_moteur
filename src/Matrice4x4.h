#pragma once
#include "Vector.h"

class Matrice4x4 {
public:
    Matrice4x4();

    // Constructeur avec des valeurs fournies
    Matrice4x4(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);

    Matrice4x4(const float matrix[16]);

    // M�thode pour calculer le produit de deux matrices 4x4
    Matrice4x4 produit(const Matrice4x4& other) const;

    // M�thode pour calculer la somme de deux matrices 4x4
    Matrice4x4 somme(const Matrice4x4& other) const;

    // M�thode pour calculer l'inverse de la matrice 4x4
    Matrice4x4 inverse() const;

    // M�thode pour transposer la matrice 4x4
    Matrice4x4 transposer() const;

    // M�thode pour calculer le d�terminant de la matrice 4x4
    float calculerDeterminant() const;

    // M�thode pour v�rifier si la matrice est carr�e
    bool estCarree() const;

    // M�thode pour v�rifier si la matrice est orthogonale
    bool estOrthogonale() const;

    // M�thode pour afficher la matrice
    void afficher() const;

    // M�thode pour obtenir les angles d'Euler
    Vector getEuler() const;

    // Surcharge de l'op�rateur "==" pour comparer deux matrices 4x4
    bool operator==(const Matrice4x4& other) const;

    // M�thode pour faire une rotation en degr�s autour de l'axe voulu :
    void rotateDeg(float angle, float axisX, float axisY, float axisZ);

    void setIdentity();

    float normalizeAngle(float angle) const;

    float calculerMinor(int row, int col) const;

    int getNbLignes() const {
        return 4;
    }

    int getNbColonnes() const {
        return 4;
    }

    bool isInversible() const;

    bool isIdentite() const;

    // Surcharge de l'op�rateur [] pour permettre l'acc�s aux �l�ments de la matrice
    float* operator[](int index);

    // Surcharge constante de l'op�rateur [] pour permettre l'acc�s aux �l�ments de la matrice constante
    const float* operator[](int index) const;

private:
    float mat[4][4];
};