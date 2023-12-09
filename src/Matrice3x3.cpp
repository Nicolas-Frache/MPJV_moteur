#include "Matrice3x3.h"
#include "Vector.h"
#include <iostream>

// Constructeur par d�faut
Matrice3x3::Matrice3x3() {
    // Initialisation de la matrice � z�ro
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mat[i][j] = 0.0;
        }
    }
}

// Constructeur avec des valeurs fournies
Matrice3x3::Matrice3x3(double m00, double m01, double m02, double m10, double m11, double m12, double m20, double m21, double m22) {
    // Initialisation de la matrice avec des valeurs
    mat[0][0] = m00;
    mat[0][1] = m01;
    mat[0][2] = m02;
    mat[1][0] = m10;
    mat[1][1] = m11;
    mat[1][2] = m12;
    mat[2][0] = m20;
    mat[2][1] = m21;
    mat[2][2] = m22;
}

// M�thode pour calculer le produit de deux matrices
Matrice3x3 Matrice3x3::produit(const Matrice3x3& other) const {
    Matrice3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.mat[i][j] = 0.0;
            for (int k = 0; k < 3; k++) {
                result.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }
    return result;
}

// M�thode pour calculer la somme de deux matrices
Matrice3x3 Matrice3x3::somme(const Matrice3x3& other) const {
    Matrice3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.mat[i][j] = mat[i][j] + other.mat[i][j];
        }
    }
    return result;
}

// M�thode pour calculer l'inverse de la matrice
Matrice3x3 Matrice3x3::inverse() const {
    Matrice3x3 result;

    double a = mat[0][0];
    double b = mat[0][1];
    double c = mat[0][2];
    double d = mat[1][0];
    double e = mat[1][1];
    double f = mat[1][2];
    double g = mat[2][0];
    double h = mat[2][1];
    double i = mat[2][2];

    double determinant = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

    if (determinant == 0.0) {
        std::cout << "Inverse non defini. Le determinant est nul." << std::endl;
        return result; // Ou une autre valeur appropri�e
    }

    result.mat[0][0] = (e * i - f * h) / determinant;
    result.mat[0][1] = (c * h - b * i) / determinant;
    result.mat[0][2] = (b * f - c * e) / determinant;
    result.mat[1][0] = (f * g - d * i) / determinant;
    result.mat[1][1] = (a * i - c * g) / determinant;
    result.mat[1][2] = (c * d - a * f) / determinant;
    result.mat[2][0] = (d * h - e * g) / determinant;
    result.mat[2][1] = (b * g - a * h) / determinant;
    result.mat[2][2] = (a * e - b * d) / determinant;

    return result;
}

// M�thode pour transposer la matrice
Matrice3x3 Matrice3x3::transposer() const {
    Matrice3x3 result;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            result.mat[i][j] = mat[j][i];
        }
    }
    return result;
}

// M�thode pour calculer le d�terminant de la matrice
double Matrice3x3::calculerDeterminant() const {
    double a = mat[0][0];
    double b = mat[0][1];
    double c = mat[0][2];
    double d = mat[1][0];
    double e = mat[1][1];
    double f = mat[1][2];
    double g = mat[2][0];
    double h = mat[2][1];
    double i = mat[2][2];

    double determinant = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);

    return determinant;
}

// M�thode pour calculer le mineur de la matrice
double Matrice3x3::calculerMinor(int i, int j) const {
    // Calculez le mineur en supprimant la ligne i et la colonne j
    double minor = 0.0;
    int row, col;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (row != i && col != j) {
                // Ne pas inclure la ligne i et la colonne j
                minor += mat[row][col];
            }
        }
    }

    return minor;
}

// M�thode pour v�rifier si la matrice est une matrice orthonorm�e
bool Matrice3x3::estOrthonormee() const {
    // V�rifie que les vecteurs de base sont orthogonaux et de longueur 1
    double tolerance = 0.0001; // Tol�rance pour la comparaison de nombres flottants

    // V�rifie que les vecteurs de base sont orthogonaux
    double dot01 = mat[0][0] * mat[1][0] + mat[0][1] * mat[1][1] + mat[0][2] * mat[1][2];
    double dot02 = mat[0][0] * mat[2][0] + mat[0][1] * mat[2][1] + mat[0][2] * mat[2][2];
    double dot12 = mat[1][0] * mat[2][0] + mat[1][1] * mat[2][1] + mat[1][2] * mat[2][2];

    if (std::abs(dot01) > tolerance || std::abs(dot02) > tolerance || std::abs(dot12) > tolerance) {
        // Les vecteurs de base ne sont pas orthogonaux
        return false;
    }

    // V�rifie que les vecteurs de base ont une longueur de 1
    double norm0 = mat[0][0] * mat[0][0] + mat[0][1] * mat[0][1] + mat[0][2] * mat[0][2];
    double norm1 = mat[1][0] * mat[1][0] + mat[1][1] * mat[1][1] + mat[1][2] * mat[1][2];
    double norm2 = mat[2][0] * mat[2][0] + mat[2][1] * mat[2][1] + mat[2][2] * mat[2][2];

    if (std::abs(norm0 - 1.0) > tolerance || std::abs(norm1 - 1.0) > tolerance || std::abs(norm2 - 1.0) > tolerance) {
        // Les vecteurs de base n'ont pas de longueur 1
        return false;
    }

    // La matrice est orthonorm�e
    return true;
}

// M�thode pour v�rifier si la matrice est orthogonale
bool Matrice3x3::estOrthogonale() const {
    // V�rifiez si la matrice est carr�e
    if (this->estCarree()) {
        // V�rifiez si la transpos�e de la matrice est �gale � son inverse
        Matrice3x3 transpose = this->transposer();
        Matrice3x3 inverse = this->inverse();

        return (transpose == inverse);
    }
    else {
        // Une matrice non carr�e ne peut pas �tre orthogonale
        return false;
    }
}

// M�thode qui calcule les angles d'Euler de la matrice
Vector Matrice3x3::getEuler() const {

    double x = 0.0, y = 0.0, z = 0.0;
    double pi = 2 * acos(0.0);

    if (mat[2][0] < 1 && mat[2][0] > -1) {
        y = -asin(mat[2][0]);

        double cos_y = cos(y);

        x = atan2(mat[2][1] / cos_y, mat[2][2] / cos_y);

        z = atan2(mat[1][0] / cos_y, mat[0][0] / cos_y);
    }
    else {
        z = 0;
        
        if (mat[2][0] < 0) {
			y = pi / 2.0;
			x = atan2(mat[0][1], mat[0][2]);
		}
        else {
			y = -pi / 2.0;
			x = atan2(-mat[0][1], -mat[0][2]);
		}

	}

    Vector euler = Vector(x, y, z);

	return euler;
}


void Matrice3x3::afficher() const {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// M�thode pour v�rifier si la matrice est carr�e
bool Matrice3x3::estCarree() const {
    return (mat[0][0] != 0.0 && mat[0][1] != 0.0 && mat[0][2] != 0.0 &&
        mat[1][0] != 0.0 && mat[1][1] != 0.0 && mat[1][2] != 0.0 &&
        mat[2][0] != 0.0 && mat[2][1] != 0.0 && mat[2][2] != 0.0);
}

bool Matrice3x3::operator==(const Matrice3x3& other) const {
    // Comparez chaque �l�ment de la matrice
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (mat[i][j] != other.mat[i][j]) {
                return false;
            }
        }
    }
    return true; // Les matrices sont �gales
}