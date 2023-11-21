#include "ofMain.h"
#include "ofApp.h"
#include "VectorTest.cpp"
#include "CustomAsserts.h"

#include "Matrice3x3Tests.cpp"

//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	
	// TESTS
	CustomAsserts ca = CustomAsserts();
	ca.beginTestClass("Tests de la classe Vector");
	vectorTestLaunch(ca);
	ca.beginTestClass("Tests de la classe Matrice3x3");
	matrice3LaunchTest(ca);

	ca.endTestSession();

	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	auto window = ofCreateWindow(settings);
	ofRunApp(window, make_shared<ofApp>());



	ofRunMainLoop();



}
