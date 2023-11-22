#include "CustomAsserts.h"
#include <CorpsRigide.h>


bool approxEqualCR(float a, float b) {
	return ceil(a * 1000) == ceil(b * 1000);
}

bool approxEqualCR(Quaternion a, Quaternion b) {
	return approxEqualCR(a.w, b.w) && approxEqualCR(a.x, b.x)
		&& approxEqualCR(a.y, b.y) && approxEqualCR(a.z, b.z);
}

void corpsRigideLaunchTest(CustomAsserts ca) {

	Particle centerCube = Particle(Vector(0, 0, 0), 1000, ofColor::blue, 10);
	CorpsRigide cube = CorpsRigide(&centerCube, 5, 15, 5, ofColor::blue);

	Quaternion q = Quaternion(.5, .5, .5, .5);
	Vector w = Vector(0, 3.14, 0);
	float dt = 2;

	Quaternion res = cube.computeNewRotation(q, w, dt);
	Quaternion excpected = Quaternion(-1.0700001, 2.0700001, 2.0700001, -1.0700001);

	std::string msg = "result = " + std::to_string(res.w) + ", " + std::to_string(res.x) + ", " + std::to_string(res.y) + ", " + std::to_string(res.z);

	ca.assertTrue(approxEqualCR(res, excpected), "test computeNewRotation");

}
