#include "CustomAsserts.h"
#include <Matrice4x4.h>

void matrice4LaunchTest(CustomAsserts ca) {

    // Test du constructeur (non inversible)
    Matrice4x4 mat(
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    );
    float det_mat = 0;

    Matrice4x4 matOrtho(
        1.0, 0.0, 0.0, 0.0,
        0.0, -1.0, 0.0, 0.0,
        0.0, 0.0, -1.0, 0.0,
        0.0, 0.0, 0.0, -1.0
    );

    // Création d'une deuxième matrice identique à la première
    Matrice4x4 mat2(
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    );
    float det_mat2 = 0;

    Matrice4x4 matInversible(
        2.0, 1.0, 0.0, 3.0,
        0.0, 3.0, -1.0, 1.0,
        1.0, 0.0, 3.0, -1.0,
        -2.0, 1.0, 3.0, 0.0
    );
    float det_matInversible = 91;

    Matrice4x4 matInversible_Inverse(
        0.0769231, 0.0659341, 0.296703, -0.274725,
        -0.0769231, 0.362637, 0.131868, - 0.010989,
        0.0769231, - 0.0769231, 0.153846, 0.153846,
        0.307692, - 0.164835, - 0.241758, 0.186813
    );


    Matrice4x4 matInversibleTranspose(
        2.0, 0.0, 1.0, -2.0,
        1.0, 3.0, 0.0, 1.0,
        0.0, -1.0, 3.0, 3.0,
        3.0, 1.0, -1.0, 0.0
    );
    //float det_matInversibleTranspose = 10;

    Matrice4x4 matNonInversible(
        1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0,
        9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0
    );

    // Produit des deux matrices
    Matrice4x4 mat3 = mat.produit(mat2);

    Matrice4x4 resultatSomme(
        2.0, 4.0, 6.0, 8.0,
        10.0, 12.0, 14.0, 16.0,
        18.0, 20.0, 22.0, 24.0,
        26.0, 28.0, 30.0, 32.0
    );

    // Test de la méthode produit
    Matrice4x4 resultatProduitMatrices = mat.produit(mat2);
    ca.assertTrue(mat3 == resultatProduitMatrices, "Produit entre matrices");

    // Test de la méthode somme
    ca.assertTrue(mat.somme(mat) == resultatSomme, "Somme");

    // Test de l'opérateur ==
    ca.assertTrue(mat == mat2, "Operator==");


    // Test de la méthode calculerDeterminant
    float resultatDeterminant_mat = mat.calculerDeterminant();
    ca.assertTrue(mat.calculerDeterminant() == resultatDeterminant_mat, "CalculerDeterminant");

    // Test de isInversible
    float resultatDeterminant_matInversible = matInversible.calculerDeterminant();
    ca.assertTrue(matInversible.isInversible() == true, "La matrice matInversible est inversible");

    // Test de isNotInversible
    float resultatDeterminant_matNonInversible = matNonInversible.calculerDeterminant();
    ca.assertTrue(matNonInversible.isInversible()== false, "La matrice matNonInversible n'est pas inversible");



    // Test de la méthode estCarree
    bool resultatCarree = (mat.getNbLignes() == mat.getNbColonnes());
    ca.assertTrue(mat.estCarree() == resultatCarree, "EstCarree");

   
    // Test de l'inverse d'une matrices
    ca.assertTrue(matOrtho.inverse() == matOrtho, "Calcule de la matrice inverse");
   

    // Test de l'opérateur ==
    ca.assertTrue(mat == mat2, "Operator== (egalite)");

    // Test de la méthode transposer
    ca.assertTrue(matInversible.transposer() == matInversibleTranspose, "Transposer");

    // Test de la méthode estOrthogonale
    Matrice4x4 matTransposed = matOrtho.transposer();
    Matrice4x4 matInverse = matOrtho.inverse();
    bool resultatOrthogonale = (matOrtho == matTransposed) && (matOrtho == matInverse);
    ca.assertTrue(matOrtho.estOrthogonale() == resultatOrthogonale, "EstOrthogonale");
    //matTransposed.afficher();
    //matInverse.afficher();
    //matOrtho.afficher();
}
