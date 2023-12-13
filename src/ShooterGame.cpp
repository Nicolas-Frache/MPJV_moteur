#include "./ShooterGame.h"
#include <ShooterGame.h>

void ShooterGame::update(){
  time += ofGetElapsedTimef();
  if(time > 1){
    time= 0.0;

    Ball* newBall = new Ball(Vector(0, 0, 0), 1, ofColor::blue, 2);
    newBall->restitution = 0.5;
    newBall->applyForce(Vector(0, 0, 40), 0.5);
    app->createParticle(newBall);
  }
}



void ShooterGame::draw(){

}

ShooterGame::ShooterGame(WorldPhysics* world, ofApp* app){
    this->world = world;
    this->app = app;
}
