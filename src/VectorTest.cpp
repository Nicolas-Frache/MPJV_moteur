#include "Vector.h"
#include <iostream>
#include "CustomAsserts.h"

int vectorTestLaunch(CustomAsserts ca) {
    // Créez quelques vecteurs pour les tests
    Vector v1(1.0, 2.0, 3.0);
    Vector v2(4.0, 5.0, 6.0);

    // Test de l'addition de vecteurs
    Vector sum = v1 + v2;
    //assert(sum == Vector(5.0, 7.0, 9.0));
    ca.assertTrue(sum == Vector(5.0, 7.0, 9.0), "addition de vecteurs");


    // Test de l'opérateur +=
    Vector v3(10.0, 20.0, 30.0);
    v3 += v1;
    ca.assertTrue(v3 == Vector(11.0, 22.0, 33.0), "operateur +=");

    // Test de l'opposé d'un vecteur
    Vector neg = -v1;
    ca.assertTrue(neg == Vector(-1.0, -2.0, -3.0), "oppose d'un vecteur");

    // Test de la soustraction de vecteurs
    Vector diff = v1 - v2;
    ca.assertTrue(diff == Vector(-3.0, -3.0, -3.0), "soustraction de vecteurs");

    // Test de l'opérateur -=
    Vector v4(100.0, 200.0, 300.0);
    v4 -= v1;
    ca.assertTrue(v4 == Vector(99.0, 198.0, 297.0), "operateur -=");

    // Test de la multiplication par un scalaire
    Vector scaled = v1 * 2.0;
    ca.assertTrue(scaled == Vector(2.0, 4.0, 6.0), "multiplication par un scalaire");

    // Test de l'opérateur *=
    Vector v5(5.0, 10.0, 15.0);
    v5 *= 3.0;
    ca.assertTrue(v5 == Vector(15.0, 30.0, 45.0), "operateur *=");

    // Test de la norme
    float norm = v1.norm();
    ca.assertTrue(ceil(norm*1000) == ceil(sqrt(14.0)*1000), "norme de vecteur"); // La norme de (1, 2, 3) est sqrt(1^2 + 2^2 + 3^2) = sqrt(14)

    // Test de la normalisation
    Vector normalized = v1.normalize();
    Vector expected = Vector(1.0 / sqrt(14.0), 2.0 / sqrt(14.0), 3.0 / sqrt(14.0));
    ca.assertTrue(
      ceil(normalized.x()*100) == ceil(expected.x()*100) 
      && ceil(normalized.y()*100) == ceil(expected.y()*100) 
      && ceil(normalized.z()*100) == ceil(expected.z()*100), "normalisation de vecteur");

    // Test du produit vectoriel
    Vector crossProduct = v1.vectoriel(v2);
    ca.assertTrue(crossProduct == Vector(-3.0, 6.0, -3.0), "produit vectoriel");

    // Test du produit scalaire
    float dotProduct = v1.scalar_product(v2);
    ca.assertTrue(dotProduct == 32.0, "produit scalaire");

    // Test de l'accès aux composantes
    ca.assertTrue(v1.x() == 1.0, "acces aux composantes x");
    ca.assertTrue(v1.y() == 2.0, "acces aux composantes y");
    ca.assertTrue(v1.z() == 3.0, "acces aux composantes z");

    return 0;
}