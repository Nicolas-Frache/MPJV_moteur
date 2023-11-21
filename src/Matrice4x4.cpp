#include "Matrice4x4.h"
#include "Matrice3x3.h"
#include <iostream>
#include <cmath>

Matrice4x4::Matrice4x4() {
    // Initialisation de la matrice à zéro
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mat[i][j] = 0.0;
        }
    }
}

Matrice4x4::Matrice4x4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33) {
    mat[0][0] = m00; mat[0][1] = m01; mat[0][2] = m02; mat[0][3] = m03;
    mat[1][0] = m10; mat[1][1] = m11; mat[1][2] = m12; mat[1][3] = m13;
    mat[2][0] = m20; mat[2][1] = m21; mat[2][2] = m22; mat[2][3] = m23;
    mat[3][0] = m30; mat[3][1] = m31; mat[3][2] = m32; mat[3][3] = m33;
}

Matrice4x4::Matrice4x4(const float matrix[16]) {
	mat[0][0] = matrix[0]; mat[0][1] = matrix[1]; mat[0][2] = matrix[2]; mat[0][3] = matrix[3];
	mat[1][0] = matrix[4]; mat[1][1] = matrix[5]; mat[1][2] = matrix[6]; mat[1][3] = matrix[7];
	mat[2][0] = matrix[8]; mat[2][1] = matrix[9]; mat[2][2] = matrix[10]; mat[2][3] = matrix[11];
	mat[3][0] = matrix[12]; mat[3][1] = matrix[13]; mat[3][2] = matrix[14]; mat[3][3] = matrix[15];
}

Matrice4x4 Matrice4x4::produit(const Matrice4x4& other) const {
    Matrice4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.mat[i][j] = 0.0;
            for (int k = 0; k < 4; k++) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }
    return result;
}

Matrice4x4 Matrice4x4::somme(const Matrice4x4& other) const {
    Matrice4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return result;
}



Matrice4x4 Matrice4x4::transposer() const {
    Matrice4x4 result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}

float Matrice4x4::calculerDeterminant() const {
    // Formule du déterminant pour une matrice 4x4
    float det =
        mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1])) -
        mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0])) +
        mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) -
        mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));

    return det;
}



bool Matrice4x4::estCarree() const {
    return (mat[0][0] != 0.0 && mat[0][1] != 0.0 && mat[0][2] != 0.0 && mat[0][3] != 0.0 &&
        mat[1][0] != 0.0 && mat[1][1] != 0.0 && mat[1][2] != 0.0 && mat[1][3] != 0.0 &&
        mat[2][0] != 0.0 && mat[2][1] != 0.0 && mat[2][2] != 0.0 && mat[2][3] != 0.0 &&
        mat[3][0] != 0.0 && mat[3][1] != 0.0 && mat[3][2] != 0.0 && mat[3][3] != 0.0);
}

bool Matrice4x4::estOrthogonale() const {
    Matrice4x4 transposed = transposer();
    Matrice4x4 result = (*this).produit(transposed);

    // Toutes les entrées diagonales de la multiplication doivent être proches de 1
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (i == j && abs(result.mat[i][j] - 1.0) > 0.01) {
                return false;
            }
            else if (i != j && abs(result.mat[i][j]) > 0.01) {
                return false;
            }
        }
    }
    return true;
}

void Matrice4x4::afficher() const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Vector Matrice4x4::getEuler() const {
    Vector euler;

    euler.set(
        normalizeAngle(atan2(mat[2][1], mat[2][2])),
        normalizeAngle(atan2(-mat[2][0], sqrt(mat[2][1] * mat[2][1] + mat[2][2] * mat[2][2]))),
        normalizeAngle(atan2(mat[1][0], mat[0][0]))
    );

	return euler;
}

bool Matrice4x4::operator==(const Matrice4x4& other) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (mat[i][j] != other.mat[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void Matrice4x4::rotateDeg(float angle, float axisX, float axisY, float axisZ) {
    float angleRad = ofDegToRad(angle);

    // Calcul des composantes sin et cos de l'angle
    float cosA = cos(angleRad);
    float sinA = sin(angleRad);

    // Normalisation de l'axe de rotation
    float length = sqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);
    if (length != 0.0f) {
        axisX /= length;
        axisY /= length;
        axisZ /= length;
    }

    // Calcul des éléments de la matrice de rotation
    float oneMinusCosA = 1.0f - cosA;
    float xy = axisX * axisY;
    float yz = axisY * axisZ;
    float xz = axisX * axisZ;

    float rotationMatrix[16] = {
        cosA + axisX * axisX * oneMinusCosA, xy * oneMinusCosA - axisZ * sinA, xz * oneMinusCosA + axisY * sinA, 0.0f,
        xy * oneMinusCosA + axisZ * sinA, cosA + axisY * axisY * oneMinusCosA, yz * oneMinusCosA - axisX * sinA, 0.0f,
        xz * oneMinusCosA - axisY * sinA, yz * oneMinusCosA + axisX * sinA, cosA + axisZ * axisZ * oneMinusCosA, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // On applique la rotation en multipliant la matrice actuelle par la matrice de rotation
    *this = this->produit(Matrice4x4(rotationMatrix));
}

void Matrice4x4::setIdentity() {
    mat[0][0] = 1; mat[0][1] = 0; mat[0][2] = 0; mat[0][3] = 0;
	mat[1][0] = 0; mat[1][1] = 1; mat[1][2] = 0; mat[1][3] = 0;
	mat[2][0] = 0; mat[2][1] = 0; mat[2][2] = 1; mat[2][3] = 0;
	mat[3][0] = 0; mat[3][1] = 0; mat[3][2] = 0; mat[3][3] = 1;
}

float Matrice4x4::normalizeAngle(float angle) const {
    while (angle > PI) {
        angle -= 2.0 * PI;
    }
    while (angle <= -PI) {
        angle += 2.0 * PI;
    }
    return angle;
}

float Matrice4x4::calculerMinor(int row, int col) const {
    // Vérifier si les indices sont valides
    if (row < 0 || row >= 4 || col < 0 || col >= 4) {
        std::cerr << "Indices de mineur non valides." << std::endl;
        return 0.0f;
    }

    // Créer une matrice 3x3 en excluant la ligne et la colonne spécifiées
    float minorMatrix[3][3];
    int minorRow, minorCol;
    for (int i = 0; i < 4; ++i) {
        if (i == row) continue;
        for (int j = 0; j < 4; ++j) {
            if (j == col) continue;
            minorRow = (i < row) ? i : i - 1;
            minorCol = (j < col) ? j : j - 1;
            minorMatrix[minorRow][minorCol] = mat[i][j];
        }
    }

    // Calculer le déterminant de la matrice 3x3 résultante
    Matrice3x3 minorMat3x3(
        minorMatrix[0][0], minorMatrix[0][1], minorMatrix[0][2],
        minorMatrix[1][0], minorMatrix[1][1], minorMatrix[1][2],
        minorMatrix[2][0], minorMatrix[2][1], minorMatrix[2][2]
    );

    return minorMat3x3.calculerDeterminant();
}

Matrice4x4 Matrice4x4::inverse() const {
    Matrice4x4 result;

    float determinant = calculerDeterminant();
    

    result[0][0] = (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1])) / determinant;
    result[0][1] = -(mat[0][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[0][2] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) + mat[0][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1])) / determinant;
    result[0][2] = (mat[0][1] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) - mat[0][2] * (mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1]) + mat[0][3] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1])) / determinant;
    result[0][3] = -(mat[0][1] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2]) - mat[0][2] * (mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1]) + mat[0][3] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1])) / determinant;

    result[1][0] = -(mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[1][2] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0])) / determinant;
    result[1][1] = (mat[0][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2]) - mat[0][2] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) + mat[0][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0])) / determinant;
    result[1][2] = -(mat[0][0] * (mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2]) - mat[0][2] * (mat[1][0] * mat[3][3] - mat[1][3] * mat[3][0]) + mat[0][3] * (mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0])) / determinant;
    result[1][3] = (mat[0][0] * (mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2]) - mat[0][2] * (mat[1][0] * mat[2][3] - mat[1][3] * mat[2][0]) + mat[0][3] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0])) / determinant;

    result[2][0] = (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) / determinant;
    result[2][1] = -(mat[0][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0]) + mat[0][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) / determinant;
    result[2][2] = (mat[0][0] * (mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][3] - mat[1][3] * mat[3][0]) + mat[0][3] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0])) / determinant;
    result[2][3] = -(mat[0][0] * (mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][3] - mat[1][3] * mat[2][0]) + mat[0][3] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0])) / determinant;

    result[3][0] = -(mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[1][1] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]) + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) / determinant;
    result[3][1] = (mat[0][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]) - mat[0][1] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]) + mat[0][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0])) / determinant;
    result[3][2] = -(mat[0][0] * (mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1]) - mat[0][1] * (mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0]) + mat[0][2] * (mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0])) / determinant;
    result[3][3] = (mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0])) / determinant;

    return result;
}



bool Matrice4x4::isInversible() const {
    float det = calculerDeterminant();
    if (det == 0.0) {
        return false;
    }
    return true;
}


bool Matrice4x4::isIdentite() const {
    Matrice4x4 matriceIdentite;
    matriceIdentite.setIdentity();

    float tolerance = 1e-6;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (abs(mat[i][j] - matriceIdentite[i][j]) >= tolerance) {
                return false;
            }
        }
    }

    return true;
}

float* Matrice4x4::operator[](int index) {
    return mat[index];
}

const float* Matrice4x4::operator[](int index) const {
    return mat[index];
}