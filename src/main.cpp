#include "ofMain.h"
#include "ofApp.h"
#include "VectorTest.cpp"
#include "CustomAsserts.h"

#include "Matrice3x3Tests.cpp"
#include "Matrice4x4Tests.cpp"
#include "QuaternionTest.cpp"
#include "CorpsRigideTests.cpp"


//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	
	// TESTS
	CustomAsserts ca = CustomAsserts();
	ca.beginTestClass("Tests de la classe Vector");
	vectorTestLaunch(ca);
	ca.beginTestClass("Tests de la classe Matrice3x3");
	matrice3LaunchTest(ca);
	ca.beginTestClass("Tests de la classe Matrice4x4");
	matrice4LaunchTest(ca);
	ca.beginTestClass("Tests de la classe Quaternion");
	quaternionLaunchTest(ca);
	ca.beginTestClass("Tests de la classe CorpsRigide");
	corpsRigideLaunchTest(ca);

	ca.endTestSession();

	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	auto window = ofCreateWindow(settings);
	ofRunApp(window, make_shared<ofApp>());



	ofRunMainLoop();



}
