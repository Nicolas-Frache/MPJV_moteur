#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){

	menu.setup();
	skybox.load();


	// R�glages de la cam�ra
	ofEnableDepthTest();
    
	// Framerate
	ofSetFrameRate(144);
	cam.setFarClip(200000);
	

	////PARTIE BLOB
	////Particle* blob = new Particle(Vector(0, 0, 0), 1, ofColor::yellow, 10);
	//moveable_Particle = &blob;
	//DampingForce* damp = new DampingForce(&blob, 0.8);
	//blob.applyForce(damp);

	//blob.addNode(new Ball(100, 0, 30, 1, ofColor::blue, 20));
	//blob.addNode(new Ball(150, 0, -30, 1, ofColor::blue, 20));
	//blob.addNode(new Ball(120, 0, 40, 1, ofColor::blue, 20));
	//blob.applyForce(20, 10, 20, 1);
	//createParticle(&blob);
	//createParticle(blob.nodes[0]);
	//createParticle(blob.nodes[1]);
	//createParticle(blob.nodes[2]);
	
	
	// Ajout particules dans la liste
	//particles.push_back(&particle1);
	//particles.push_back(&particle2);
	//particles.push_back(&particle3);


	// Créez une matrice mat1
	//Matrice3x3 mat1(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
	Matrice3x3 mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

	// Affichez mat1
	std::cout << "Matrice mat1 :" << std::endl;
	mat1.afficher();

	// Créez une matrice mat2
	Matrice3x3 mat2(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);

	// Affichez mat2
	std::cout << "Matrice mat2 :" << std::endl;
	mat2.afficher();

	// Calculez le produit de mat1 et mat2 et affichez le résultat
	Matrice3x3 mat3 = mat1.produit(mat2);
	std::cout << "Produit de mat1 et mat2 (mat3) :" << std::endl;
	mat3.afficher();

	// Calculez le déterminant de mat1 et affichez-le
	float determinant = mat1.calculerDeterminant();
	std::cout << "Determinant de mat1 : " << determinant << std::endl;

	// Vérifiez si mat1 est orthonormée et affichez le résultat
	if (mat1.estOrthonormee()) {
		std::cout << "La matrice mat1 est orthonormee." << std::endl;
	}
	else {
		std::cout << "La matrice mat1 n'est pas orthonormee." << std::endl;
	}

	// Calculez et affichez l'inverse de mat1
	Matrice3x3 inverseMat1 = mat1.inverse();
	std::cout << "Inverse de mat1 :" << std::endl;
	inverseMat1.afficher();

	// Calculez et affichez la transposée de mat1
	Matrice3x3 transposedMat1 = mat1.transposer();
	std::cout << "Transposée de mat1 :" << std::endl;
	transposedMat1.afficher();

	//// Calculez et affichez le mineur de mat1 à l'emplacement (1, 1)
	//float minor = mat1.calculerMinor(1, 1);
	//std::cout << "Mineur de mat1 à l'emplacement (1, 1) : " << minor << std::endl;

	if (mat1 == mat2) {
		std::cout << "Les matrices sont egales." << std::endl;
	}
	else {
		std::cout << "Les matrices ne sont pas egales." << std::endl;
	}

	//PARTIE CORPS RIGIDES
	cube.applyForce(Vector(1,1,0), 0.1);
	cube.applyTorque(Vector(100, 100, 100), 20);
	corpsRigides.push_back(&cube);
	world.addCorps(&cube); //je sais pas si la liste corpsRigides est utile puisqu'on utilise world
}

//--------------------------------------------------------------
void ofApp::update() {

	world.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
	menu.draw();
	cam.begin();
    skybox.draw();
	ofDrawGrid(50, 5, true, true, true, false);

	// Draw particules
	for (Particle* particle : particles) {
		particle->draw();
	}
	for (CorpsRigide* corps : corpsRigides) {
		corps->draw();
	}
	cam.end();
}

void ofApp::createParticle(Particle* particle) {
	particles.push_back(particle);
	world.addParticle(particle);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	Vector camPos;
	Vector camDir;
	if (key == '1' || key == '2' || key == '3') {
		camPos = Vector(cam.getPosition().x, cam.getPosition().y, cam.getPosition().z);
		auto tmp = cam.getLookAtDir();
		camDir = Vector(tmp.x, tmp.y, tmp.z);
	}


	if (key == '1') {
		Ball* newBall = new Ball(camPos, 1, ofColor::blue, 20);
		newBall->restitution = 0.5;
		newBall->applyForce(camDir * 100, 0.5);
		createParticle(newBall);
	}

	if (key == '2') {
		Fireball* newFireball = new Fireball(camPos, 1);
		newFireball->restitution = 0.8;
		newFireball->applyForce(camDir * 110, 0.5);
		createParticle(newFireball);
	}

	if (key == '3') {
		Laser* newLaser = new Laser(camPos, camDir, 1, ofColor::black, 3);
		newLaser->applyForce(camDir * 200, 0.5);
		createParticle(newLaser);
	}

	float speed = 100;

	if (key == OF_KEY_UP) { //on applique une force vers le haut de durée courte
		moveable_Particle->applyForce(0, 0, speed, 0.1);
	}
	if (key == OF_KEY_DOWN) {
		moveable_Particle->applyForce(0, 0, -speed, 0.1);
	}
	if (key == OF_KEY_LEFT) {
		moveable_Particle->applyForce(speed, 0, 0, 0.1);
	}
	if (key == OF_KEY_RIGHT) {
		moveable_Particle->applyForce(-speed, 0, 0, 0.1);
	}
	if (key == 32) { //on applique une force pour sauter de durée courte
		moveable_Particle->applyForce(0, 100, 0, 0.1);
	}
	if (key == OF_KEY_RETURN) {
		blob.splitBlob();
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	// Contrôles de la caméra lors du clic droit
	cam.toggleControl();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
