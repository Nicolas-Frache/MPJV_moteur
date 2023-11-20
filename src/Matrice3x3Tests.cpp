#include "CustomAsserts.h"
#include <Matrice3x3.h>

void matrice3LaunchTest(CustomAsserts ca) {

  // Test du constructeur
  Matrice3x3 mat(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  Matrice3x3 mat2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
  Matrice3x3 mat3 = mat.produit(mat2);



  // Test de la méthode produit
  ca.assertTrue(mat.produit(mat.transposer()) == Matrice3x3(14.0, 32.0, 50.0, 32.0, 77.0, 122.0, 50.0, 122.0, 194.0), "Produit");
  ca.assertTrue(mat.somme(mat) == Matrice3x3(2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0), "Somme");
  ca.assertTrue(mat == Matrice3x3(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0), "Operator==");

  // Test de la méthode transposer
  ca.assertTrue(mat.transposer() == Matrice3x3(1.0, 4.0, 7.0, 2.0, 5.0, 8.0, 3.0, 6.0, 9.0), "Transposer");
  ca.assertTrue(mat.calculerDeterminant() == 0.0, "CalculerDeterminant | determinant null");
  ca.assertTrue(mat.estOrthogonale() == false, "EstOrthogonale | faux");
  ca.assertTrue(mat.estCarree() == true, "EstCarree | vrai ");

  ca.assertTrue(mat3 == Matrice3x3(30.0, 36.0, 42.0, 66.0, 81.0, 96.0, 102.0, 126.0, 150.0), "Produit entre matrices");

}