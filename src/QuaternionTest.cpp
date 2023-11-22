#include "CustomAsserts.h"
#include "Quaternion.h"
using namespace std;

bool approxEqual(float a, float b) {
  return ceil(a * 100000000) == ceil(b * 100000000);
}

bool approxEqual(Quaternion a, Quaternion b) {
  return approxEqual(a.w, b.w) && approxEqual(a.x, b.x) 
    && approxEqual(a.y, b.y) && approxEqual(a.z, b.z);
}


void quaternionLaunchTest(CustomAsserts ca) {

  Quaternion q1; // Initialise un quaternion à l'élément neutre
  Quaternion q2(0.5, 0.5, 0.5, 0.5);
  Quaternion q3(1, 2, 3, 4);
  Quaternion qy = Quaternion(0, 0, 1, 0);
  Quaternion qx = Quaternion(0, 1, 0, 0);
  Quaternion qw = Quaternion(1, 0, 0, 0);

  ca.assertTrue(q2 == q2 && q1 == q1 && !(q1 == q2), "Operateur ==");
  ca.assertTrue(!(q2 != q2) && q1 != q2, "Operateur !=");
  ca.assertTrue(approxEqual(q3.norm(), sqrt(30)), "Norme");

  Quaternion q3n = Quaternion(1, 2, 3, 4).normalize();
  ca.assertTrue(approxEqual(q3n.norm(), 1), "Normalisation");

  ca.assertTrue(q2.conjugate() == Quaternion(0.5, -0.5, -0.5, -0.5), "Conjugaison");
  ca.assertTrue(approxEqual(q3.inverse(), q3n.conjugate()/q3n.norm()), "Inverse");

  ca.assertTrue((qy * qx == Quaternion(0, 0, 0, -1)), "Produit d'Hamilton #1");
  ca.assertTrue(approxEqual(Quaternion(0, sqrt(.5), sqrt(.5), 0) * Quaternion(0, 0, sqrt(.5), sqrt(.5)), 
    Quaternion(-.5, .5, -.5, .5)), "Produit d'Hamilton #2");

  ca.assertTrue(approxEqual(q3n.dotProduct(q3n), 1), "Produit Scalaire == 1");
  ca.assertTrue(qy.dotProduct(qx) == 0, "Produit Scalaire == 0 ");
  
  ca.assertTrue(approxEqual(q3n.power(1), q3n), "Exponentation, t=1");
  ca.assertTrue(approxEqual(qy.power(.5), Quaternion(sqrt(.5), 0, sqrt(.5), 0)), "Exponentation, t= 1/2");
  ca.assertTrue(approxEqual(qy.power(0), qw), "Exponentation, t= 0");

  Quaternion(0, 0, 1, 0).power(1).print();
  Quaternion(0, 0, 1, 0).power(.5).print();
  Quaternion(0, 0, 1, 0).power(0).print();


}

