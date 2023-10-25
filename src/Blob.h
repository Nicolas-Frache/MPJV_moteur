#pragma once
#include "Particle.h"
#include <Ball.h>

class Blob : public Ball {
    //� voir si on fait une particule avec un certain nombre de liaisons possibles (genre hexagone par ex)
    //ou si on fait une liste de voisins ? �a peut se faire
    //par contre �a serait un peu d�gueu en brut de faire tout les voisinages sur le ofApp 
    //genre on a part1 part2 et part3
    //faut appliquer ressortA sur part1 et part2, ressortB sur part2 et part3, ressortC sur part3 et part1 par ex
    //du coup 6 forces � appliquer
public: 
    Blob(Vector position, float invertedMass, ofColor color, float size);
    void addNode(Ball* ball);
    
    void update() override;

    vector<Ball*> nodes;

    // Split le blob en envoyant voler la moiti� de ses celulles
    void splitBlob();

    bool Blob::resolveInterpenetration(Particle& other) override;
    void Blob::resolveRestingContactWith(Particle& other) override;

};

