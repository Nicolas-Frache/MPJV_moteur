#include "VectorTest.h"

int main() {
    // Créez quelques vecteurs pour les tests
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);

    // Test de l'addition de vecteurs
    Vector sum = v1 + v2;
    assert(sum == Vector(5.0, 7.0, 9.0));

    // Test de l'opérateur +=
    Vector v3(10.0, 20.0, 30.0);
    v3 += v1;
    assert(v3 == Vector(11.0, 22.0, 33.0));

    // Test de l'opposé d'un vecteur
    Vector neg = -v1;
    assert(neg == Vector(-1.0, -2.0, -3.0));

    // Test de la soustraction de vecteurs
    Vector diff = v1 - v2;
    assert(diff == Vector(-3.0, -3.0, -3.0));

    // Test de l'opérateur -=
    Vector v4(100.0, 200.0, 300.0);
    v4 -= v1;
    assert(v4 == Vector(99.0, 198.0, 297.0));

    // Test de la multiplication par un scalaire
    Vector scaled = v1 * 2.0;
    assert(scaled == Vector(2.0, 4.0, 6.0));

    // Test de l'opérateur *=
    Vector v5(5.0, 10.0, 15.0);
    v5 *= 3.0;
    assert(v5 == Vector(15.0, 30.0, 45.0));

    // Test de la norme
    float norm = v1.norm();
    assert(norm == sqrt(14.0)); // La norme de (1, 2, 3) est sqrt(1^2 + 2^2 + 3^2) = sqrt(14)

    // Test de la normalisation
    Vector normalized = v1.normalize();
    assert(normalized == Vector(1.0 / sqrt(14.0), 2.0 / sqrt(14.0), 3.0 / sqrt(14.0)));

    // Test du produit vectoriel
    Vector crossProduct = v1.vectoriel(v2);
    assert(crossProduct == Vector(-3.0, 6.0, -3.0));

    // Test du produit scalaire
    float dotProduct = v1.scalar_product(v2);
    assert(dotProduct == 32.0);

    // Test de l'accès aux composantes
    assert(v1.x() == 1.0);
    assert(v1.y() == 2.0);
    assert(v1.z() == 3.0);

    std::cout << "Tous les tests ont réussi." << std::endl;

    return 0;
}